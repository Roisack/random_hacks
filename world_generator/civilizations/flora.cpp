#include "flora.hpp"
#include "region.hpp"
#include <stdio.h>

Flora::Flora(long t)
{
    fprintf(stderr, "New plant born\n");
    alive = true;
    birthTime = t;
    life = 100.0f;
    expectedLifeTime = 1000;
    lastReproduced = t;
    lastEaten = t;
}

Flora::~Flora()
{
}

void Flora::advanceTime(long t)
{
    if (region->getTemperature() < minTemperature || region->getTemperature() > maxTemperature
        || region->getHumidity() < minHumidity || region->getHumidity() > maxHumidity)
    {
        takeDamage(life/2);
    }
    if (t > birthTime + expectedLifeTime)
    {
        takeDamage(life/2);
    }

    if (t > lastReproduced + spreadRate)
    {
        lastReproduced = t;
        region->spreadFlora(this);
    }

    if (t > lastEaten + eatDelay)
    {
        lastEaten = t;

        // If there is no food, take damage and shorten food request time
        float receivedFood = region->givePlantFood(this);
        if (receivedFood < requiredSustenance)
        {
            takeDamage(0.01f);

            // How large % did we get?
            float percentage = receivedFood / requiredSustenance;

            // 100% == Next food time is as usual
            // 50% == Ask food when half of the usual time has passed
            lastEaten -= eatDelay*percentage;
        }
    }
}

void Flora::takeDamage(float d)
{
    life -= d;
    if (life <= 1)
        die();
}

void Flora::die()
{
    fprintf(stderr, "Plant is dying\n");
    alive = false;
    region->reportDeadPlantToWorld();
    region = NULL;
}

void Flora::setCoordX(int x)
{
    coord_x = x;
}

void Flora::setCoordY(int y)
{
    coord_y = y;
}

void Flora::setRegion(Region* r)
{
    region = r;
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

int Flora::getCoordX()
{
    return coord_x;
}

int Flora::getCoordY()
{
    return coord_y;
}

Region* Flora::getRegion()
{
    return region;
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

float Flora::getRequiredSustenance()
{
    return requiredSustenance;
}

void Flora::setRequiredSustenance(float r)
{
    requiredSustenance = r;
}

void Flora::setEatDelay(long t)
{
    eatDelay = t;
}

long Flora::getEatDelay()
{
    return eatDelay;
}
