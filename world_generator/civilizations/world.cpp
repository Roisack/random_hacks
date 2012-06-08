#include "world.hpp"
#include "region.hpp"

World::World()
{
    fprintf(stderr, "World is alive\n");
    alive = true;
    world_time = 0;
}

World::~World()
{
    die();
}

void World::addRegion(int x, int y, int t, int h)
{
    std::shared_ptr<Region> r = std::shared_ptr<Region>(new Region());
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
