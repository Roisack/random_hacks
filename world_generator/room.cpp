#include "room.hpp"
#include "manager.hpp"
#include "renderer.hpp"


Room::Room(std::string s, std::string mus, int n, int t)
{
    fprintf(stderr, "Room creating with name %s and number %d and type %d\n", s.c_str(), n, t);
    name = s;
    roomNumber = n;
    roomType = t;
    music = mus;
    firstRun = true;
}

Room::~Room()
{
}

boost::shared_ptr<Sprite> Room::findSprite(std::string toSearch)
{
    for (spriteIterator = spriteMap.begin(); spriteIterator != spriteMap.end(); spriteIterator++)
    {
        if (((*spriteIterator).first.compare(toSearch) == 0))
        {
            fprintf(stderr, "Found\n");
            return (*spriteIterator).second;
        }
    }
    fprintf(stderr, "No such sprite %s in room %d\n", toSearch.c_str(), roomNumber);
    return boost::shared_ptr<Sprite>();
}

void Room::createWorld()
{
    worldSprite = findSprite("world");
    SDL_Color col;
    col.r = 255.0f;
    col.g = 1.0f;
    col.b = 1.0f;
    worldSprite->setAllPixels(worldSprite->spriteSurface, col);
    worldSprite->createClouds();
}

void Room::operate()
{
	if (roomType == 1)	// An arena
	{
        if (firstRun)
        {
            createWorld();
            firstRun = false;
        }

        for (spriteIterator = spriteMap.begin(); spriteIterator != spriteMap.end(); spriteIterator++)
            (*spriteIterator).second->render();

        for (modelIterator = modelMap.begin(); modelIterator != modelMap.end(); modelIterator++)
            (*modelIterator).second->render();
	} else if (roomType == 3) // Cinematics
    {
        renderer.moveCamera(0, 0, renderer.getNativeHeight());
        if (firstRun)
        {
            roomStartTime = manager.getTime();
            timePerPicture = 4;
            pictureChangeTime = roomStartTime;
            spriteIterator = spriteMap.begin();
            firstRun = false;
        }

        if (manager.getTime() - pictureChangeTime > timePerPicture)
        {
            pictureChangeTime = manager.getTime();
            spriteIterator++;
        }
        if (spriteIterator == spriteMap.end())
            manager.getRoomMgr()->nextRoom();
        else
            (*spriteIterator).second->render();
	} else if (roomType == 4) // Static text rooms
    {
        renderer.moveCamera(0, 0, renderer.getNativeHeight());
        if (firstRun)
        {
            spriteIterator = spriteMap.begin();
            firstRun = false;
        }

        if (spriteIterator == spriteMap.end())
            manager.getRoomMgr()->nextRoom();
        else
            (*spriteIterator).second->render();
    }
}

boost::shared_ptr<Sprite> Room::getSprite(std::string name)
{
    spriteIterator = spriteMap.find(name.c_str());
    if (spriteIterator != spriteMap.end())
    {
        return spriteMap[name.c_str()];
    } else
    {
        fprintf(stderr, "Requested sprite not found! Sprite: %s, room: %d", name.c_str(), roomNumber);
        boost::shared_ptr<Sprite> nullPointer;
        return nullPointer;
    }
}

void Room::addSprite(std::string name, boost::shared_ptr<Sprite> s)
{
    spriteMap[name] = s;
}

void Room::removeSprite(std::string name)
{
    spriteIterator = spriteMap.find(name.c_str());
    if (spriteIterator != spriteMap.end())
    {
        spriteMap.erase(spriteIterator);
    } else
    {
        fprintf(stderr, "No sprite found to delete! Sprite: %s, Room: %d", name.c_str(), roomNumber);
    }
}

void Room::iterateSprites()
{
    spriteIterator++;
}

void Room::addModel(std::string name, boost::shared_ptr<Object3D> m)
{
    modelMap[name] = m;
}

void Room::removeModel(std::string name)
{
    modelIterator = modelMap.find(name.c_str());
    if (modelIterator != modelMap.end())
    {
        modelMap.erase(modelIterator);
    } else
    {
        fprintf(stderr, "No model found to delete! Sprite: %s, Room: %d", name.c_str(), roomNumber);
    }
}
