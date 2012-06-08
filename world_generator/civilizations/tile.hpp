#ifndef __TILE_HPP_
#define __TILE_HPP_

#include <vector>
#include <memory>

class Region;
class Creature;
class Flora;

class Tile
{
private:
    int coord_x;
    int coord_y;
    float plantFoodValue;
    float temperature;
    float humidity;
    std::vector<std::shared_ptr<Creature> > creatures;
    std::vector<std::shared_ptr<Flora> > flora;
public:
    Tile(int x, int y);
    ~Tile();
    
    void die();
    void addCreature(std::shared_ptr<Creature> c);
    void addFlora(std::shared_ptr<Flora> f);
    float takePlantFood(float q);
    void addPlantFood(float q);

    void setCoordX(int x);
    void setCoordY(int y);
    void setHumidity(float h);
    void setTemperature(float t);
    void setPlantFoodValue(float v);
    int getCoordX();
    int getCoordY();
    float getHumidity();
    float getTemperature();
    float getPlantFoodValue();
    std::vector<std::shared_ptr<Creature> > getCreatures();
    std::vector<std::shared_ptr<Flora> > getFlora();
};

#endif
