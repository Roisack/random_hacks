#include "world.hpp"

World::World()
{
    alive = true;
}

World::~World()
{
}

void World::live()
{
    while (alive)
    {
        advanceTime();
    }
}

void World::advanceTime()
{
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
