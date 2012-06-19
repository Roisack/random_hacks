#ifndef __REGION_HPP_
#define __REGION_HPP_

#include <memory>
#include <vector>
#include <map>
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
    
    float plant_food_available;
    float plants_consume_food;

    Tile* regionMap[32][32];
    float temperature;  // Kelvins
    float humidity; // Percentage
    std::map<std::shared_ptr<Creature>, int> fauna; // Various animals in the area
    std::map<std::shared_ptr<Flora>, int> flora;    // A map containing a type of a plant, and a number of them in the area
    std::map<std::shared_ptr<Flora>, int> flora_to_spread; // A map containing a type of a plant, and a number of them that wants to spread
   std::map<std::shared_ptr<Flora>, int> flora_to_delete;   // A map containing quantities of various plants that are dying
   
    
    long lastProduction;  // When did the region last add new resources for plants
    int productionDelay;

    int numberOfPlantTypes;
    int numberOfAnimalTypes;
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
    void removeDeadPlants();

    void queryPlants(long t);
    void queryFauna(long t);

    void setWorld(World* world);
    void setActive(bool b);
    void addFauna(std::shared_ptr<Creature>& c, int i);
    void addFlora(std::shared_ptr<Flora>& f, int i);
    void reportDeadPlantsToWorld(int q);
    void reportDeadCreaturesToWorld(int q);
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
    std::map<std::shared_ptr<Creature>, int >* getFauna();
    std::map<std::shared_ptr<Flora>, int >* getFlora();
};

#endif
