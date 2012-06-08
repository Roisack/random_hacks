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
}

Region::~Region()
{
    die();
}

void Region::createPlantLife()
{
    // Choose a plant from a list of available plants based on the region,
    // neighboring regions, temperature, humidity
}

void Region::advanceTime(float t)
{
    // Add new resources
    for (int i = 0; i < size_x; i++)
    {
        for (int j = 0; j < size_y; j++)
        {
            float regrowth = produceNewPlantFood();
            regionMap[i][j]->addPlantFood(regrowth);
        }
    }

    std::vector<std::shared_ptr<Creature> >::iterator iter;
    for (iter = fauna.begin(); iter != fauna.end(); iter++)
    {
        (*iter)->advanceTime(t);
    }

    std::vector<std::shared_ptr<Flora> >::iterator iter2;
    for (iter2 = flora.begin(); iter2 != flora.end(); iter2++)
    {
        (*iter)->advanceTime(t);
    }
}

// Add some new resources for plants
float Region::produceNewPlantFood()
{
    float output = 10;

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
    std::vector<std::shared_ptr<Flora> >::iterator iter;
    for (iter = flora.begin(); iter != flora.end(); iter++)
        (*iter)->die();

    std::vector<std::shared_ptr<Creature> >::iterator iter2;
    for (iter2 = fauna.begin(); iter2 != fauna.end(); iter2++)
        (*iter2)->die();

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
void Region::addFauna(std::shared_ptr<Creature> c)
{
    if (tbox.searchElementFromVector(fauna, c) == fauna.end())
    {
        c->setRegion(this);
        fauna.push_back(c);
        regionMap[c->getCoordX()][c->getCoordY()]->addCreature(c);
    }
}

void Region::addFlora(std::shared_ptr<Flora> f)
{
    if (tbox.searchElementFromVector(flora, f) == flora.end())
    {
        f->setRegion(this);
        flora.push_back(f);
        regionMap[f->getCoordX()][f->getCoordY()]->addFlora(f);
    }
}

// When a plant reproduces, it spreads a new instance of itself with some modifications nearby
void Region::spreadFlora(Flora* f)
{
    int new_coord_X = f->getCoordX();
    new_coord_X = tbox.giveRandomInt(-1*new_coord_X, new_coord_X);
    int new_coord_Y = f->getCoordY();
    new_coord_Y = tbox.giveRandomInt(-1*new_coord_Y, new_coord_Y);
    std::shared_ptr<Flora> new_plant = std::shared_ptr<Flora>(new Flora(world->getTime()));
    new_plant->setCoordX(new_coord_X);
    new_plant->setCoordY(new_coord_Y);
    addFlora(new_plant);
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

std::vector<std::shared_ptr<Creature> > Region::getFauna()
{
    return fauna;
}

std::vector<std::shared_ptr<Flora> > Region::getFlora()
{
    return flora;
}

bool Region::getActive()
{
    return active;
}
