#ifndef TPSTRATEGY_CONSOLECONTROLLER_H
#define TPSTRATEGY_CONSOLECONTROLLER_H

#include "Controller.h"
#include "UnitModuleType.h"
#include <windows.h>
#include "string"
#include "vector"
#include "unordered_map"

enum class Color{
    DarkBlue = 9,
    Green = 10,
    Blue = 11,
    Red = 12,
    Crimson = 13,
    Yellow = 14,
    White = 15,
};

enum class Command{
    Help,
    Info,
    Clear,
    Skip,
    Go,
    Attack,
    Mine,
    Die,
    Create,
};

class ConsoleController : public Controller{
public:
    ConsoleController(int partyNum);

    ~ConsoleController() override = default;

    void PerformActions() override;

private:
    const int TileWidth = 3;

    HANDLE hConsole;
    int partyNum;

    static bool IsStaticInitialised;

    void DrawField() const;

    void DrawNumbers(int length) const;

    void Print(std::string text, int colorNum  = 15) const;

    void DrawHead() const;

    void Clear() const;

    void Redraw() const;

    std::vector<std::string> ReadLine();

    //return whether it's end
    bool PerformCommand();

    bool GetPosition(int& x, int& y, std::vector<std::string>& strs, int i0);

    bool GetPosition(int& x, std::vector<std::string>& strs, int i0);

    bool GetUnit(Unit*& unit, std::vector<std::string>& strs, int i0, bool sameColor);

    void UnitInfo(Unit& unit) const;

    void CreateAction(Unit& unit, std::vector<UnitModuleType>& modules);

    void GoAction(Unit& unit, int x);

    void AttackAction(Unit& unit1, int x, int y);

    void MineAction(Unit& unit);

    static void StaticInit();

    static std::string Pad(std::string str, int size, char paddingChar = ' ');

    static int PartyColors[2];

    static std::unordered_map<std::string, Command> StrToCommand;

    static std::unordered_map<std::string, UnitModuleType> StrToModule;

    static std::string HelpText;
};


#endif
