#include "flora.hpp"

Flora::Flora()
{
}

Flora::~Flora()
{
}

void Flora::setMass(float m)
{
    mass = m;
}

void Flora::setWidth(float w)
{
    width = w;
}

void Flora::setHeight(float h)
{
    height = h;
}

void Flora::setType(std::string t)
{
    type = t;
}

void Flora::setName(std::string n)
{
    name = n;
}

void Flora::setMinTemperature(float t)
{
    minTemperature = t;
}

void Flora::setMaxTemperature(float t)
{
    maxTemperature = t;
}

void Flora::setMinHumidity(float h)
{
    minHumidity = h;
}

void Flora::setMaxHumidity(float h)
{
    maxHumidity = h;
}

void Flora::setSpreadRate(float r)
{
    spreadRate = r;
}

float Flora::getWidth()
{
    return width;
}

float Flora::getHeight()
{
    return height;
}

float Flora::getMass()
{
    return mass;
}

std::string Flora::getType()
{
    return type;
}

std::string Flora::getName()
{
    return name;
}

float Flora::getMinTemperature()
{
    return minTemperature;
}

float Flora::getMaxTemperature()
{
    return maxTemperature;
}

float Flora::getMinHumidity()
{
    return minHumidity;
}

float Flora::getMaxHumidity()
{
    return maxHumidity;
}

float Flora::getSpreadRate()
{
    return spreadRate;
}
