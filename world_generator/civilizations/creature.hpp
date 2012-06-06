#ifndef __CREATURE_HPP_
#define __CREATURE_HPP_

#include <string>
#include <vector>
#include <memory>
class Civilization;
class House;

class Creature
{
private:
    int id;
protected:
    std::string name;
    std::string type;
    float mass;
    float height;
    float width;
    float age;
    float expectedDyingAge;

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
    Creature();
    ~Creature();

    void setMass(float m);
    void setHeight(float h);
    void setWidth(float d);
    void setAge(float a);
    void setArms(unsigned short a);
    void setLegs(unsigned short l);
    void setWings(unsigned short w);
    void setTails(unsigned short t);
    void setHeads(unsigned short h);
    void setSkinMaterial(std::string s);
    void setBodyMaterial(std::string b);

    float getMass();
    float getHeight();
    float getWidth();
    float getAge();
    unsigned short getArms();
    unsigned short getLegs();
    unsigned short getWings();
    unsigned short getHeads();
    unsigned short getTails();
    std::string getSkinMaterial();
    std::string getBodyMaterial();
};

#endif
