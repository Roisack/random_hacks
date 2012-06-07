#include "region.hpp"
#include "creature.hpp"
#include "flora.hpp"
#include "toolbox.hpp"

Region::Region()
{
    size_x = 32;
    size_y = 32;
}

Region::~Region()
{
}

void Region::addFauna(std::shared_ptr<Creature> c)
{
    // Add new fauna if it doesn't exist already
    if (tbox.searchElementFromVector(fauna, c) != fauna.end())
        fauna.push_back(c);
}

void Region::addFlora(std::shared_ptr<Flora> f)
{
    flora.push_back(f);
}

void Region::setTemperature(float t)
{
    temperature = t;
}

float Region::getTemperature()
{
    return temperature;
}

std::vector<std::shared_ptr<Creature> > Region::getFauna()
{
    return fauna;
}

std::vector<std::shared_ptr<Flora> > Region::getFlora()
{
    return flora;
}
