#include "human.hpp"

Human::Human(float t) : Creature(t)
{
    heads = 1;
    legs = 2;
    arms = 2;
    tails = 0;
    wings = 0;
    age = 0.00f;
    skinMaterial = "soft_skin";
    bodyMaterial = "human_muscle";
    name = "human_no_name";
    type = "human";
    expectedDyingAge = 1.0f;
}

Human::~Human()
{
}
