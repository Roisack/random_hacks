#include "world.hpp"
#include "region.hpp"
#include <stdio.h>
#include <iostream>

World::World()
{
    fprintf(stderr, "World is alive\n");
    alive = true;
    world_time = 0;
    currentCreatures = 0;
    pastCreatures = 0;
    currentPlants = 0;
    pastPlants = 0;
    currentCivilizations = 0;
    maxCreaturesInWorld = 100000000; // 100 million
    maxPlantsInWorld = 100000000;   // 100 million
}

World::~World()
{
    die();
}

void World::addRegion(int x, int y, int t, int h)
{
    std::shared_ptr<Region> r = std::shared_ptr<Region>(new Region());
    r->setWorld((World*)this);
    r->setCoordX(x);
    r->setCoordY(y);
    r->setTemperature(t);
    r->setHumidity(h);
    r->createPlantLife();
    regions.push_back(r);
}

void World::live()
{
    addRegion(0, 0, 25, 50);
    while (alive)
    {
        advanceTime();
        fprintf(stderr, "World time: %ld\n", world_time);
    }
}

void World::die()
{
    fprintf(stderr, "World is dying\n");
    // Destroy all regions. This should be recursive, destroying everything in those regions
    std::vector<std::shared_ptr<Region> >::iterator iter;
    for (iter = regions.begin(); iter != regions.end(); iter++)
        (*iter)->die();
}

void World::advanceTime()
{
    world_time++;
    if (world_time % 10 == 0)
        report();
    std::vector<std::shared_ptr<Region> >::iterator iter;
    for (iter = regions.begin(); iter != regions.end(); iter++)
        (*iter)->advanceTime(world_time);

    std::vector<std::shared_ptr<Civilization> >::iterator iter2;
    for (iter2 = civilizations.begin(); iter2 != civilizations.end(); iter2++)
        (*iter)->advanceTime(world_time);
}

void World::report()
{
    fprintf(stderr, "==========================================================\n");
    fprintf(stderr, "Civilizations\tCreatures\tPlants\tpastCreatures\tpastPlants\n");
    fprintf(stderr, "%d\t\t\%d\t\t\%d\t\t\%d\t\t\%d\n", currentCivilizations, currentCreatures, currentPlants, pastCreatures, pastPlants);
    fprintf(stderr, "==========================================================\n");
    //std::string dummy;
    //std::cin >> dummy;
}

void World::setTime(long t)
{
    world_time = t;
}

long World::getTime()
{
    return world_time;
}

std::vector<std::shared_ptr<Civilization> > World::getCivilizations()
{
    return civilizations;
}

unsigned long World::getCurrentCreatures()
{
    return currentCreatures;
}

unsigned long World::getPastCreatures()
{
    return pastCreatures;
}

unsigned long World::getCurrentPlants()
{
    return currentPlants;
}

unsigned long World::getPastPlants()
{
    return pastPlants;
}

bool World::allowedToSpawnCreature()
{
    if (currentCreatures > maxCreaturesInWorld)
        return false;
    return true;
}

bool World::allowedToSpawnPlant()
{
    if (currentPlants > maxPlantsInWorld)
        return false;
    return true;
}

void World::reportNewCreatures(int n)
{
    currentCreatures += n;
}

void World::reportDeadCreatures(int n)
{
    currentCreatures -= n;
    pastCreatures += n;
}

void World::reportNewPlants(int n)
{
    currentPlants += n;
}

void World::reportDeadPlants(int n)
{
    currentPlants -= n;
    pastPlants += n;
}
