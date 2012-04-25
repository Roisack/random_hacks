#include "roommanager.hpp"
#include "toolbox.hpp"
#include "shader.hpp"
#include "shader_interference.hpp"
#include "shader_perlinnoise.hpp"
#include "shader_plasma.hpp"
#include "shader_template.hpp"
#include "shader_normalMap.hpp"
#include "shader_perVertexLighting.hpp";
#include "terrain.hpp"
#ifdef WIN32
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif

typedef std::pair<std::string, boost::shared_ptr<Room> > roomPair;

RoomManager::RoomManager()
{
    fprintf(stderr, "RoomManager constructing...\n");
}

RoomManager::~RoomManager()
{
    fprintf(stderr, "RoomManager destructing...\n");
}

bool RoomManager::init()
{   
    fprintf(stderr, "RoomManager creating rooms\n");
    boost::shared_ptr<Room> introRoom(new Room("Intro", "no music", 1, 3));
    boost::shared_ptr<Room> room1Ptr(new Room("Shader room", "", 100, 1));

    std::string path1 = "data/2D/logo_1024x1024.png";
    boost::shared_ptr<Sprite> introSpritePtr1(new Sprite(path1));
    introRoom->addSprite("intro picture", introSpritePtr1);
    roomVector.push_back(introRoom);

    std::string temp = "data/2D/stars_1024x1024.png";
    boost::shared_ptr<Sprite> shader_surface(new Sprite(temp));

    //boost::shared_ptr<Shader> shaderPtr(new Shader("simple.vert", "simple.frag"));
    boost::shared_ptr<ShaderInterference> shaderPtr(new ShaderInterference("interference.vert", "interference.frag"));
    //boost::shared_ptr<ShaderNormalMap> shaderPtr(new ShaderNormalMap("normalMap.vert", "normalMap.frag"));
    //boost::shared_ptr<ShaderPerlinNoise> shaderPtr(new ShaderPerlinNoise("perlinnoise.vert", "perlinnoise.frag"));
    //boost::shared_ptr<ShaderPlasma> shaderPtr(new ShaderPlasma("plasma.vert", "plasma.frag"));
    shader_surface->addShader(shaderPtr);

    room1Ptr->addSprite("shader_surface", shader_surface);

    temp = "data/2D/heightMap_terrain_128x128.png";
    //boost::shared_ptr<Terrain> terrainPtr = boost::shared_ptr<Terrain>(new Terrain(128, 128, "data/2D/heightMap_sphere_128x128.png", 100.0f));
    //room1Ptr->addTerrain("First Terrain", terrainPtr);

    arenaRoom = room1Ptr;
    roomVector.push_back(room1Ptr);

    boost::shared_ptr<Room> helpRoom(new Room("Help", "no music", 900, 4));
    path1 = "data/2D/help.png";
    boost::shared_ptr<Sprite> helpSpritePtr(new Sprite(path1));
    helpRoom->addSprite("help", helpSpritePtr);
    roomVector.push_back(helpRoom);

    activeRoom = 0;
    return true;
}

boost::shared_ptr<Room> RoomManager::getRoom(std::string name)
{
    for (roomIter = roomVector.begin(); roomIter != roomVector.end(); roomIter++)
    {
        if ((*roomIter)->getName().compare(name))
            return (*roomIter);
    }

    fprintf(stderr, "Requested room not found: %s", name.c_str());
    boost::shared_ptr<Room> nullPointer;
    return nullPointer;
}

int RoomManager::getRoomIndex(std::string name)
{
    int i = 0;
    for (roomIter = roomVector.begin(); roomIter != roomVector.end(); roomIter++)
    {
        if ((*roomIter)->getName().compare(name) == 0)
            return i;
        i++;
    }

    fprintf(stderr, "Requested room not found: %s", name.c_str());
    return -1;
}

void RoomManager::addRoom(boost::shared_ptr<Room> r)
{
}

void RoomManager::work()
{
    if (activeRoom < roomVector.size() && activeRoom >= 0)
        roomVector.at(activeRoom)->operate();
    else
        fprintf(stderr, "Room error, this is bad! Panic! D: :<\n");
}

void RoomManager::nextRoom()
{
    if (roomVector.size() > activeRoom)
        activeRoom++;
}

void RoomManager::changeRoom(std::string name)
{
    int index = getRoomIndex(name);
    if (index >= 0 && index < roomVector.size())
        activeRoom = index;
    else
        fprintf(stderr, "Cannot change room to index %d in roomVector of size %d", index, roomVector.size());
}

boost::shared_ptr<Room> RoomManager::giveCurrentRoom()
{
    return roomVector.at(activeRoom);
}
