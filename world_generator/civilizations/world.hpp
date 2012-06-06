#ifndef __WORLD_HPP_
#define __WORLD_HPP_

class Civilization;

#include <memory>
#include <vector>

class World
{
private:
    int width;  // Multiple of 8 (km) (0, 8, 16, 24, 32...)
    int height; // Multiple of 8 (km)
    std::vector<std::shared_ptr<Civilization> > civilizations;
    unsigned long currentCreatures;
    unsigned long pastCreatures;
    bool alive;
public:
    World();
    ~World();
    
    void live();
    void advanceTime();
    std::vector<std::shared_ptr<Civilization> > getCivilizations();
    unsigned long getCurrentCreatures();
    unsigned long getPastCreatures();
};

#endif
