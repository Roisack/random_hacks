#include "goblin.hpp"

Goblin::Goblin(float t) : Creature(t)
{
    heads = 1;
    legs = 2;
    arms = 2;
    tails = 0;
    wings = 0;
    age = 0.00f;
    skinMaterial = "soft_skin";
    bodyMaterial = "goblin_muscle";
    name = "goblin_no_name";
    type = "goblin";
    expectedDyingAge = 1.0f;
}

Goblin::~Goblin()
{
}
