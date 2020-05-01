#include "Server.h"

Server::Server(Controller& c1, Controller& c2) : game(){
    controllers.push_back(&c1);
    c1.SetGame(game);
    controllers.push_back(&c2);
    c2.SetGame(game);
}

//return winner number
int Server::Run(){
    for (int i = 0;game.End() == -1;i = (i + 1) % controllers.size()){
        game.OnNewTurn(i);
        controllers[i]->PerformActions();
    }
    return game.End();
}