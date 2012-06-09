#ifndef __REGION_HPP_
#define __REGION_HPP_

#include <memory>
#include <vector>

class Creature;
class Flora;
class World;
class Tile;

class Region
{
private:
    World* world;
    bool active;
    unsigned short int size_x;  // Kilometres
    unsigned short int size_y;
    int coord_x;
    int coord_y;
    
    Tile* regionMap[32][32];
    float temperature;  // Kelvins
    float humidity; // Percentage
    std::vector<std::shared_ptr<Creature> > fauna; // Various animals in the area
    std::vector<std::shared_ptr<Flora> > flora; // Various plants in the area
    std::vector<std::shared_ptr<Flora> > flora_toSpread;    // Temp container for new flora
public:
    Region();
    ~Region();

    void advanceTime(float t);
    void die();
    void spreadFlora(Flora* f);
    float givePlantFood(Flora* f);
    float produceNewPlantFood();
    void createPlantLife();
    void addPendingFlora();

    void setWorld(World* world);
    void setActive(bool b);
    void addFauna(std::shared_ptr<Creature> c);
    void addFlora(std::shared_ptr<Flora> f);
    void reportDeadPlantToWorld();
    void reportDeadCreatureToWorld();
    void setTemperature(float t);
    void setHumidity(float h);
    void setCoordX(int x);
    void setCoordY(int y);
    int getCoordX();
    int getCoordY();
    World* getWorld();
    bool getActive();
    float getTemperature();
    float getHumidity();
    std::vector<std::shared_ptr<Creature> > getFauna();
    std::vector<std::shared_ptr<Flora> > getFlora();
};

#endif
