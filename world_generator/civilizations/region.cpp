#include "region.hpp"
#include "creature.hpp"
#include "flora.hpp"
#include "toolbox.hpp"
#include "world.hpp"
#include "tile.hpp"
#include <vector>
#include <stdio.h>

Region::Region()
{
    fprintf(stderr, "Creating new region\n");
    size_x = 32;
    size_y = 32;
    for (int i = 0; i < size_x; i++)
    {
        for (int j = 0; j < size_y; j++)
        {
            regionMap[i][j] = new Tile(i,j);
        }
    }
    lastProduction = 0;
    productionDelay = 10;
    plant_food_available = 5000;
    numberOfPlantTypes = 0;
    numberOfAnimalTypes = 0;
}

Region::~Region()
{
    die();
}

void Region::createPlantLife()
{
    // TODO:
    // Choose a plant from a list of available plants based on the region,
    // neighboring regions, temperature, humidity

    // Add some quantity of each type of plant that this regino supports

    // Placeholder: add some generic plants of 4 different types
    std::shared_ptr<Flora> f1 = std::shared_ptr<Flora>(new Flora(world->getTime()));
    f1->setCoordX(tbox.giveRandomInt(0,32));
    f1->setCoordY(tbox.giveRandomInt(0, 32));
    f1->setMinHumidity(10);
    f1->setMaxHumidity(100);
    f1->setMinTemperature(15);
    f1->setMaxTemperature(40);
    f1->setName("Generic plant");
    f1->setSpreadRate(20);
    f1->setMass(0.1f);
    f1->setHeight(0.2f);
    f1->setWidth(0.1f);
    f1->setType("shrub");
    f1->setRequiredSustenance(2.0f);
    f1->setEatDelay(30);
    f1->setSpreadQuantity(10);
    f1->setLife(30);
    addFlora(f1, 100);

    std::shared_ptr<Flora> f2 = std::shared_ptr<Flora>(new Flora(world->getTime()));
    f2->setCoordX(tbox.giveRandomInt(0,32));
    f2->setCoordY(tbox.giveRandomInt(0, 32));
    f2->setMinHumidity(20);
    f2->setMaxHumidity(100);
    f2->setMinTemperature(20);
    f2->setMaxTemperature(45);
    f2->setName("Generic tropical plant");
    f2->setSpreadRate(10);
    f2->setMass(0.1f);
    f2->setHeight(0.3f);
    f2->setWidth(0.1f);
    f2->setType("shrub");
    f2->setRequiredSustenance(3.0f);
    f2->setEatDelay(20);
    f2->setSpreadQuantity(30);
    f2->setLife(15);
    addFlora(f2, 100);

    std::shared_ptr<Flora> f3 = std::shared_ptr<Flora>(new Flora(world->getTime()));
    f3->setCoordX(tbox.giveRandomInt(0,32));
    f3->setCoordY(tbox.giveRandomInt(0, 32));
    f3->setMinHumidity(5);
    f3->setMaxHumidity(60);
    f3->setMinTemperature(-40);
    f3->setMaxTemperature(35);
    f3->setName("Pine");
    f3->setSpreadRate(150);
    f3->setMass(500.0f);
    f3->setHeight(7.0f);
    f3->setWidth(0.7f);
    f3->setType("tree");
    f3->setRequiredSustenance(15.0f);
    f3->setEatDelay(100);
    f3->setSpreadQuantity(2);
    f3->setLife(300);
    addFlora(f3, 100);

    std::shared_ptr<Flora> f4 = std::shared_ptr<Flora>(new Flora(world->getTime()));
    f4->setCoordX(tbox.giveRandomInt(0,32));
    f4->setCoordY(tbox.giveRandomInt(0, 32));
    f4->setMinHumidity(5);
    f4->setMaxHumidity(60);
    f4->setMinTemperature(-40);
    f4->setMaxTemperature(35);
    f4->setName("Cactus");
    f4->setSpreadRate(150);
    f4->setMass(50.0f);
    f4->setHeight(1.2f);
    f4->setWidth(0.5f);
    f4->setType("tree");
    f4->setRequiredSustenance(10.0f);
    f4->setEatDelay(500);
    f4->setSpreadQuantity(1);
    f4->setLife(500);
    addFlora(f4, 100);

    plants_consume_food = 0.0f;
    numberOfPlantTypes = 0;

    std::map<std::shared_ptr<Flora>, int>::iterator iter;
    for (iter = flora.begin(); iter != flora.end(); iter++)
    {
        fprintf(stderr, "Calculating plant food needs %f * %d\n", (*iter).first->getRequiredSustenance(), (*iter).second);
        numberOfPlantTypes++;
        plants_consume_food += (*iter).first->getRequiredSustenance() * (*iter).second;
        fprintf(stderr, "%d plant types now require %f food\n", numberOfPlantTypes, plants_consume_food);
    }
}

void Region::removeDeadPlants()
{
    // Delete a number of plants of each type
    std::map<std::shared_ptr<Flora>, int>::iterator grim_reaper;

    if (flora_to_delete.size() < 1)
        fprintf(stderr, "No plants need deleting\n");

    for (grim_reaper = flora_to_delete.begin(); grim_reaper != flora_to_delete.end(); grim_reaper++)
    {
        fprintf(stderr, "Removing %d plants of type %s\n", (*grim_reaper).second, (*grim_reaper).first->getName().c_str());
        if ((*grim_reaper).second > flora[(*grim_reaper).first])
            (*grim_reaper).second = flora[(*grim_reaper).first];
        flora[(*grim_reaper).first] -= (*grim_reaper).second;
        reportDeadPlantsToWorld((*grim_reaper).second);
    }
}

void Region::reportDeadPlantsToWorld(int quantity)
{
    world->reportDeadPlants(quantity);
}

void Region::reportDeadCreaturesToWorld(int quantity)
{
    world->reportDeadCreatures(quantity);
}

void Region::queryPlants(long t)
{
    std::map<std::shared_ptr<Flora>, int>::iterator tempIter;

    // Give resources to the plants in weighted quantities
    int total_plants_requesting = 0;
    int total_food_requirement = 0;
    std::map<std::shared_ptr<Flora>, int>::iterator iter;
    std::map<std::shared_ptr<Flora>, int> plants_that_want_food;
    for (iter = flora.begin(); iter != flora.end(); iter++)
    {
        if (t > (*iter).first->getEatDelay() + (*iter).first->getLastEaten())
        {
            total_plants_requesting += (*iter).second;
            total_food_requirement += (*iter).first->getRequiredSustenance() * (*iter).second;
            fprintf(stderr, "Total plants requesting is now %d and total food requirement is now %d\n", total_plants_requesting, total_food_requirement);
            plants_that_want_food[(*iter).first] = (*iter).second;
        }
    }

    std::map<std::shared_ptr<Flora>, int> food_to_give;
    std::map<std::shared_ptr<Flora>, int>::iterator food_iter;
    int food_for_these_plants = 0;
    
    if (total_food_requirement > plant_food_available && total_food_requirement > 0)
    {
        // Not enough food. Distribute available food evenly
        for (food_iter = plants_that_want_food.begin(); food_iter != plants_that_want_food.end(); food_iter++)
        {
            fprintf(stderr, "About to do maths: %d / %d * %f\n", total_plants_requesting, (*food_iter).second, plant_food_available);
            if ((*food_iter).second > 0)
            {
                food_for_these_plants = total_plants_requesting / (*food_iter).second * plant_food_available;
                food_to_give[(*food_iter).first] = food_for_these_plants;

                // Kill the plants that were left without food :(
                flora_to_delete[(*food_iter).first] = (*food_iter).second - ((food_for_these_plants / ((*food_iter).second * (*food_iter).first->getRequiredSustenance())) * (*food_iter).second) * 0.1f;
            }
        }
        plant_food_available = 0;
    } else if (total_food_requirement > 0)
    {
        for (food_iter = plants_that_want_food.begin(); food_iter != plants_that_want_food.end(); food_iter++)
        {
            fprintf(stderr, "Giving food: ");
            fprintf(stderr, "%s\n", (*food_iter).first->getName().c_str());
            fprintf(stderr, "%f\n", (*food_iter).first->getRequiredSustenance());
            food_to_give[(*food_iter).first] = (*food_iter).first->getRequiredSustenance() * (*food_iter).second;;
            plant_food_available -= (*food_iter).first->getRequiredSustenance() * (*food_iter).second;
        }
    }

    std::map<std::shared_ptr<Flora>, int>::iterator spread_iter;
    for (spread_iter = flora.begin(); spread_iter != flora.end(); spread_iter++)
    {
        if (t > (*spread_iter).first->getLastReproduced() + (*spread_iter).first->getSpreadRate())
        {
            flora_to_spread[(*spread_iter).first] = (*spread_iter).first->getSpreadQuantity();
            (*iter).first->setLastReproduced(t);
        }
    }

    // See if new plants were born
    if (flora_to_spread.size() > 0)
    {
        addPendingFlora();
    }

    // See if plants have died
    if (flora_to_delete.size() > 0)
    {
        removeDeadPlants();
    }
}

void Region::queryFauna(long t)
{
}

void Region::advanceTime(float t)
{
    // Add new resources
    if (t > lastProduction + productionDelay)
    {
        float regrowth = produceNewPlantFood();
        plant_food_available += regrowth;
        lastProduction = t;
    }

    fprintf(stderr, "About to remove dead plants\n");
    fprintf(stderr, "done\n");

    queryPlants(t);
    queryFauna(t);
}

// Add some new resources for plants
float Region::produceNewPlantFood()
{
    float output = 10000;

    int r = tbox.giveRandomInt(0,10);
    output *= 0.5f*r;
    if (temperature < 0)
    {
        output = 0;
    }
    else if (temperature < 10)
    {
        output /= 2;
    } else if (temperature > 40)
    {
        output /= 2;
    }

    if (humidity < 20)
    {
        output /= 2;
    }

    return output;
}

void Region::die()
{
    fprintf(stderr, "Region is dying\n");
    world = NULL;
    std::map<std::shared_ptr<Flora>, int >::iterator iter;
    for (iter = flora.begin(); iter != flora.end(); iter++)
        (*iter).first->die();

    std::map<std::shared_ptr<Creature>, int>::iterator iter2;
    for (iter2 = fauna.begin(); iter2 != fauna.end(); iter2++)
        (*iter2).first->die();

    for (int i = 0; i < size_x; i++)
    {
        for (int j = 0; j < size_y; j++)
        {
            if (regionMap[i][j] != NULL)
            {
                regionMap[i][j]->die();
                regionMap[i][j] = NULL;
            }
        }
    }

    active = false;
}

// Add new fauna if it doesn't exist already
void Region::addFauna(std::shared_ptr<Creature>& c, int n)
{
    c->setRegion(this);
    fauna[c] += n;
    regionMap[c->getCoordX()][c->getCoordY()]->addCreature(c);
    world->reportNewCreatures(n);
}

void Region::addFlora(std::shared_ptr<Flora>& f, int n)
{
    f->setRegion(this);
    flora[f] = n;
    regionMap[f->getCoordX()][f->getCoordY()]->addFlora(f);
    world->reportNewPlants(n);
}

// When a plant reproduces, it spreads a new instance of itself with some modifications nearby
void Region::spreadFlora(Flora* f)
{
    if (world->allowedToSpawnPlant() == false)
    {
        fprintf(stderr, "World forbids spawning new plants\n");
        return;
    }
    int new_coord_X = f->getCoordX();
    new_coord_X = tbox.giveRandomInt(0, 32);
    int new_coord_Y = f->getCoordY();
    new_coord_Y = tbox.giveRandomInt(0, 32);
    std::shared_ptr<Flora> new_plant = std::shared_ptr<Flora>(new Flora(world->getTime()));
new_plant->setCoordX(new_coord_X);
    new_plant->setCoordY(new_coord_Y);
    new_plant->setEatDelay(f->getEatDelay());
    new_plant->setRequiredSustenance(f->getRequiredSustenance());
    new_plant->setHeight(f->getHeight());
    new_plant->setWidth(f->getWidth());
    new_plant->setMass(f->getMass());
    new_plant->setMaxHumidity(f->getMaxHumidity());
    new_plant->setMinHumidity(f->getMinHumidity());
    new_plant->setMinTemperature(f->getMinTemperature());
    new_plant->setMaxTemperature(f->getMaxTemperature());
    new_plant->setName(f->getName());
    new_plant->setType(f->getType());
    new_plant->setSpreadRate(f->getSpreadRate());
    new_plant->setRegion(this);
    new_plant->setSpreadQuantity(f->getSpreadQuantity());
    flora_to_spread[new_plant] = new_plant->getSpreadQuantity();
}

// After we are done handling our flora vector, add new things to it
void Region::addPendingFlora()
{
    std::map<std::shared_ptr<Flora>, int >::iterator iter;
    for (iter = flora_to_spread.begin(); iter != flora_to_spread.end(); iter++)
    {
        fprintf(stderr, "Spreading new flora: %d\n", (*iter).second);
        flora[(*iter).first] += (*iter).second;
        world->reportNewPlants((*iter).second);
    }
    flora_to_spread.clear();
}

// A plant consumes some resources, or attempts to do so
float Region::givePlantFood(Flora* f)
{
    float result = regionMap[f->getCoordX()][f->getCoordY()]->takePlantFood(f->getRequiredSustenance());
    return result;
}

void Region::setWorld(World* w)
{
    world = w;
}

void Region::setActive(bool b)
{
    active = b;
}

void Region::setTemperature(float t)
{
    temperature = t;
}

void Region::setHumidity(float h)
{
    humidity = h;
}

void Region::setCoordX(int x)
{
    coord_x = x;
}

void Region::setCoordY(int y)
{
    coord_y = y;
}

int Region::getCoordX()
{
    return coord_x;
}

int Region::getCoordY()
{
    return coord_y;
}

World* Region::getWorld()
{
    return world;
}

float Region::getTemperature()
{
    return temperature;
}

float Region::getHumidity()
{
    return humidity;
}

std::map<std::shared_ptr<Creature>, int >* Region::getFauna()
{
    return &fauna;
}

std::map<std::shared_ptr<Flora>, int >* Region::getFlora()
{
    return &flora;
}

bool Region::getActive()
{
    return active;
}
