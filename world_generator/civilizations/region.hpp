#ifndef __REGION_HPP_
#define __REGION_HPP_

#include <memory>
#include <vector>

class Creature;
class Flora;

class Region
{
private:
    unsigned short int size_x;  // Kilometres
    unsigned short int size_y;
    float temperature;  // Kelvins
    std::vector<std::shared_ptr<Creature> > fauna; // Various animals in the area
    std::vector<std::shared_ptr<Flora> > flora; // Various plants in the area
public:
    Region();
    ~Region();

    void addFauna(std::shared_ptr<Creature> c);
    void addFlora(std::shared_ptr<Flora> f);
    void setTemperature(float t);
    float getTemperature();
    std::vector<std::shared_ptr<Creature> > getFauna();
    std::vector<std::shared_ptr<Flora> > getFlora();
};

#endif
