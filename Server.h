#ifndef TPSTRATEGY_SERVER_H
#define TPSTRATEGY_SERVER_H

#include "Controller.h"
#include "Game.h"
#include "vector"

class Server {
public:
    Server(Controller& p1, Controller& p2);

    int Run();
protected:
    std::vector<Controller*> controllers;
    Game game;
};


#endif
