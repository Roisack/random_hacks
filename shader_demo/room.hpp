#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include <boost/shared_ptr.hpp>
#include "sprite.hpp"
#include "object3d.hpp"
#include "terrain.hpp"
#include <map>

typedef std::map<std::string, boost::shared_ptr<Sprite> > spriteContainer;
typedef std::map<std::string, boost::shared_ptr<Object3D> > modelContainer;
typedef std::map<std::string, boost::shared_ptr<Terrain> > terrainContainer;
class Room
{
private:
    std::string name;
    int roomNumber;
    int roomType;

    spriteContainer spriteMap;
    spriteContainer::iterator spriteIterator;

    modelContainer modelMap;
    modelContainer::iterator modelIterator;

    terrainContainer terrainMap;
    terrainContainer::iterator terrainIterator;

    double roomStartTime;
    bool firstRun;
    double timePerPicture; // For cinematics
    double pictureChangeTime; // For cinematics
    std::string music;

    boost::shared_ptr<Sprite> worldSprite;

public:
    Room(std::string s, std::string mus, int n, int t);
    ~Room();
    void operate();
    boost::shared_ptr<Sprite> getSprite(std::string name);
    void addSprite(std::string name, boost::shared_ptr<Sprite> s);
    void removeSprite(std::string name);
    void iterateSprites();
    void toggleShaders();
    void shaderAction1();
    void shaderAction2();
    void shaderAction3();
    void shaderAction4();
    void shaderAction5();
    void shaderAction6();
    void shaderAction7();
    void shaderAction8();

    void addModel(std::string name, boost::shared_ptr<Object3D> m);
    void removeModel(std::string name);

    void addTerrain(std::string name, boost::shared_ptr<Terrain> t);
    void removeTerrain(std::string name);

    boost::shared_ptr<Sprite> findSprite(std::string f);
    boost::shared_ptr<Object3D> findModel(std::string f);
    boost::shared_ptr<Terrain> findTerrain(std::string f);

    std::string getName() { return name; }
    int getType() { return roomType; }
};

#endif
