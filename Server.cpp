#include "Server.h"

Server::Server(Controller& c1, Controller& c2) : game(){
    controllers.push_back(&c1);
    controllers.push_back(&c2);
}

//return winner number
int Server::Run(){
    for (int i = 0;game.End() == -1;i = (i + 1) % controllers.size()){
        controllers[i]->PerformActions(game);
    }
    return game.End();
}