#include "creature.hpp"
#include <stdio.h>

Creature::Creature(long t)
{
    fprintf(stderr, "New creature born\n");
    birthTime = t;
}

Creature::~Creature()
{
    die();
}

void Creature::advanceTime(long t)
{
}

void Creature::die()
{
    fprintf(stderr, "Creature is dying\n");
    region = NULL;
    active = false;
}

void Creature::setCoordX(int x)
{
    coord_x = x;
}

void Creature::setCoordY(int y)
{
    coord_y = y;
}

void Creature::setRegion(Region* r)
{
    region = r;
}

void Creature::setMass(float m)
{
    mass = m;
}

void Creature::setHeight(float h)
{
    height = h;
}

void Creature::setWidth(float w)
{
    width = w;
}

void Creature::setAge(long a)
{
    age = a;
}

void Creature::setArms(unsigned short a)
{
    arms = a;
}

void Creature::setLegs(unsigned short l)
{
    legs = l;
}

void Creature::setHeads(unsigned short h)
{
    heads = h;
}

void Creature::setTails(unsigned short t)
{
    tails = t;
}

void Creature::setWings(unsigned short w)
{
    wings = w;
}

void Creature::setSkinMaterial(std::string s)
{
    skinMaterial = s;
}

void Creature::setBodyMaterial(std::string s)
{
    bodyMaterial = s;
}

int Creature::getCoordX()
{
    return coord_x;
}

int Creature::getCoordY()
{
    return coord_y;
}

Region* Creature::getRegion()
{
    return region;
}

float Creature::getMass()
{
    return mass;
}

float Creature::getHeight()
{
    return height;
}

float Creature::getWidth()
{
    return width;
}

long Creature::getAge()
{
    return age;
}

unsigned short Creature::getArms()
{
    return arms;
}

unsigned short Creature::getLegs()
{
    return legs;
}

unsigned short Creature::getWings()
{
    return wings;
}

unsigned short Creature::getHeads()
{
    return heads;
}

unsigned short Creature::getTails()
{
    return tails;
}

std::string Creature::getSkinMaterial()
{
    return skinMaterial;
}

std::string Creature::getBodyMaterial()
{
    return bodyMaterial;
}
