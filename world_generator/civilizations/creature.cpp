#include "creature.hpp"

Creature::Creature()
{
}

Creature::~Creature()
{
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

void Creature::setAge(float a)
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

float Creature::getAge()
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
