#ifndef _MANAGER_HPP_
#define _MANAGER_HPP_

#include <vector>
#include <boost/shared_ptr.hpp>
#include "opengl.hpp"
#include "roommanager.hpp"

class Manager
{
private:
    int id;
    int argc;
    char** argv;
    bool running;
    int nextFPS;
    float gameTime;
    bool debug;
    boost::shared_ptr<Opengl> openglPtr;
    boost::shared_ptr<RoomManager> roomManagerPtr;
public:
    Manager();
    ~Manager();
    int run();
    void stop();
    void setParams(int argc, char** args);
    double getTime() { return gameTime; }
    void getEnter();
    boost::shared_ptr<Opengl> getOpengl() { return openglPtr; }
    boost::shared_ptr<RoomManager> getRoomMgr() { return roomManagerPtr; }
};

extern Manager manager;

#endif
