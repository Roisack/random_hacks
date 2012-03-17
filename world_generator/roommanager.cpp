#include "roommanager.hpp"
#include "toolbox.hpp"
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
    std::string path1 = "data/2D/logo_1024x1024.png";
    boost::shared_ptr<Sprite> introSpritePtr1(new Sprite(path1));
    introRoom->addSprite("intro picture", introSpritePtr1);
    roomVector.push_back(introRoom);
   
    boost::shared_ptr<Room> room1Ptr(new Room("World room", "", 100, 1));
    boost::shared_ptr<Sprite> world(new Sprite(std::string("data/2D/stars_1024x1024.png")));
    room1Ptr->addSprite("world", world);
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
