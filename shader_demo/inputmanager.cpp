#include "inputmanager.hpp"
#include "manager.hpp"

#ifdef WIN32
#include <SDL.h>
#include <windows.h>
#else
#include <SDL/SDL.h>
#endif

Inputmanager inputmgr;

Inputmanager::Inputmanager()
{
    fprintf(stderr, "Inputmanager being hired...\n");
}

Inputmanager::~Inputmanager()
{
    fprintf(stderr, "Inputmanager being fired...\n");
}

// Resets all keys as pressable at the beginning of the loop
// TODO: Make into a keystate array
void Inputmanager::resetKeys()
{
    triggeredLeft = false;
    triggeredRight = false;
    triggeredUp = false;
    triggeredDown = false;
    triggeredA = false;
    triggeredD = false;
    triggeredZ = false;
    triggeredX = false;
    triggeredK = false;
}

void Inputmanager::checkInput()
{
    boost::shared_ptr<Room> currentRoom = manager.getRoomMgr()->giveCurrentRoom();
    if (currentRoom->getType() == 3 || currentRoom->getType() == 4)  // cinematics / text
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                    manager.stop();
                    break;

                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            currentRoom->iterateSprites();
                            break;
                        case SDLK_RETURN:
                            currentRoom->iterateSprites();
                            break;
                    }
                    break;
            }
        }
    } else
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                    manager.stop();
                    break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            manager.stop();
                            break;
                        case SDLK_a:
                            currentRoom->toggleShaders();
                            break;
                        case SDLK_q:
                            currentRoom->shaderAction1();
                            break;
                        case SDLK_w:
                            currentRoom->shaderAction2();
                            break;
                        case SDLK_e:
                            currentRoom->shaderAction3();
                            break;
                        case SDLK_r:
                            currentRoom->shaderAction4();
                            break;
                    }
                break;
            }
        }
    }
}
