#ifndef TPSTRATEGY_CONSOLECONTROLLER_H
#define TPSTRATEGY_CONSOLECONTROLLER_H

#include "Controller.h"

class ConsoleController : Controller{
public:
    ~ConsoleController() override = default;

    void PerformActions(Game& game) override;

private:
    void DrawGame(Game& game) const;

    void DrawNumbers(int length) const;
};


#endif
