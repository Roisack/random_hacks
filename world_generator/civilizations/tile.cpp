#include "tile.hpp"
#include "creature.hpp"
#include "flora.hpp"

Tile::Tile(int x, int y)
{
    coord_x = x;
    coord_y = y;
}

Tile::~Tile()
{
}

void Tile::die()
{
    creatures.clear();
    flora.clear();
}

void Tile::addCreature(std::shared_ptr<Creature> c)
{
    creatures.push_back(c);
}

void Tile::addFlora(std::shared_ptr<Flora> f)
{
    flora.push_back(f);
}

// Take some plant food from this tile
float Tile::takePlantFood(float quantity)
{
    float output = 0;
    if (plantFoodValue < quantity)
        output = plantFoodValue;
    else
        output = quantity;
    plantFoodValue -= quantity;
    return output;
}

void Tile::addPlantFood(float quantity)
{
    plantFoodValue += quantity;
}

void Tile::setCoordX(int x)
{
    coord_x = x;
}

void Tile::setCoordY(int y)
{
    coord_y = y;
}

void Tile::setHumidity(float h)
{
    humidity = h;
}

void Tile::setTemperature(float t)
{
    temperature = t;
}

void Tile::setPlantFoodValue(float v)
{
    plantFoodValue = v;
}

float Tile::getHumidity()
{
    return humidity;
}

float Tile::getTemperature()
{
    return temperature;
}

float Tile::getPlantFoodValue()
{
    return plantFoodValue;
}

int Tile::getCoordX()
{
    return coord_x;
}

int Tile::getCoordY()
{
    return coord_y;
}

std::vector<std::shared_ptr<Creature> > Tile::getCreatures()
{
    return creatures;
}

std::vector<std::shared_ptr<Flora> > Tile::getFlora()
{
    return flora;
}
