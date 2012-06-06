#ifndef __FLORA_HPP_
#define __FLORA_HPP_

// Flora means plant. Like a cactus

#include <string>

class Flora
{
private:
    std::string type;
    std::string name;
    float height;
    float width;
    float mass;
    float minTemperature;  // In how cold does this plant survive
    float maxTemperature;  // In how hot does this plant survive
    float minHumidity; // How humid must the region be, at least
    float maxHumidity; // How humid can the region be, at max
    float spreadRate;  // How fast does the plant reproduce
public:
    Flora();
    ~Flora();

    void setMass(float m);
    void setHeight(float h);
    void setWidth(float h);
    void setType(std::string t);
    void setName(std::string n);
    void setMinTemperature(float t);
    void setMaxTemperature(float t);
    void setMinHumidity(float h);
    void setMaxHumidity(float h);
    void setSpreadRate(float r);

    float getHeight();
    float getWidth();
    float getMass();
    std::string getType();
    std::string getName();
    float getMinTemperature();
    float getMaxTemperature();
    float getMinHumidity();
    float getMaxHumidity();
    float getSpreadRate();
};

#endif
