#ifndef __CREATURE_HPP_
#define __CREATURE_HPP_

#include <string>
#include <vector>
#include <memory>
class Civilization;
class House;
class Region;

class Creature
{
private:
    int id;
protected:
    int coord_x;
    int coord_y;
    std::string name;
    std::string type;
    float mass;
    float height;
    float width;
    long age;
    long expectedDyingAge;
    long birthTime;
    bool active;

    // Where this creature currently is
    Region* region;

    // Number of varius limbs
    unsigned short arms;
    unsigned short legs;
    unsigned short wings;
    unsigned short heads;
    unsigned short tails;
    std::string skinMaterial;
    std::string bodyMaterial;

    // Social stuff
    std::shared_ptr<Civilization> civiliationPtr;
    std::shared_ptr<House> housePtr;
public:
    Creature(long t);
    ~Creature();

    void advanceTime(long t);
    void die();

    void setCoordX(int x);
    void setCoordY(int y);
    void setRegion(Region* r);
    void setMass(float m);
    void setHeight(float h);
    void setWidth(float d);
    void setAge(long a);
    void setArms(unsigned short a);
    void setLegs(unsigned short l);
    void setWings(unsigned short w);
    void setTails(unsigned short t);
    void setHeads(unsigned short h);
    void setSkinMaterial(std::string s);
    void setBodyMaterial(std::string b);

    int getCoordX();
    int getCoordY();
    Region* getRegion();
    float getMass();
    float getHeight();
    float getWidth();
    long getAge();
    unsigned short getArms();
    unsigned short getLegs();
    unsigned short getWings();
    unsigned short getHeads();
    unsigned short getTails();
    std::string getSkinMaterial();
    std::string getBodyMaterial();
};

#endif
