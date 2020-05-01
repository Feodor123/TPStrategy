#include "ConsoleController.h"
#include "Entity.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include "Game.h"
#include "Unit.h"
#include "ConfigLoader.h"

using namespace std;

string ConsoleController::HelpText;

bool ConsoleController::IsStaticInitialised = false;

int ConsoleController::PartyColors[] = {static_cast<int>(Color::Red),static_cast<int>(Color::Blue)};

unordered_map<std::string, Command> ConsoleController::StrToCommand{
        {"help",   Command::Help},
        {"info",   Command::Info},
        {"clear",  Command::Clear},
        {"skip",   Command::Skip},
        {"create", Command::Create},
        {"go",     Command::Go},
        {"attack", Command::Attack},
        {"mine",   Command::Mine},
        {"die",    Command::Die},
};

unordered_map<std::string, UnitModuleType> ConsoleController::StrToModule{
        {"atk1", UnitModuleType::Attack1},
        {"atk2", UnitModuleType::Attack2},
        {"atk3", UnitModuleType::Attack3},
        {"mine1", UnitModuleType::Mine1},
        {"mine2", UnitModuleType::Mine2},
        {"mine3", UnitModuleType::Mine3},
};

ConsoleController::ConsoleController(int partyNum) {
    if (!IsStaticInitialised){
        StaticInit();
        IsStaticInitialised = true;
    }
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    this->partyNum = partyNum;
}

void ConsoleController::PerformActions() {
    Redraw();
    while (!PerformCommand());
}

void ConsoleController::Redraw() const {
    Clear();
    DrawHead();
    DrawField();
}

void ConsoleController::DrawField() const {
    DrawNumbers(game->fieldLength);
    for (int h = 0;h < game->fieldWidth;++h){
        for (int i = 0;i < game->fieldLength;++i){
            if (game->tiles[i].entities.size() > h)
                Print(Pad(to_string(game->tiles[i].entities[h]->HP()), TileWidth), PartyColors[game->tiles[i].entities[h]->Color()]);
            else
                Print(Pad("",TileWidth));
        }
        Print("\n");
    }
    Print(Pad("",TileWidth * game->fieldLength, '=') + '\n');
}

void ConsoleController::Print(string text, int colorNum) const {
    SetConsoleTextAttribute(hConsole, colorNum);
    cout << text;
}

void ConsoleController::DrawNumbers(int length) const {
    string str1;
    for (int i = 0;i < length;++i)
        str1 += Pad(to_string(i + 1), TileWidth);
    Print(str1 + '\n');
}

void ConsoleController::DrawHead() const {
    Print("Print \"help\" command to get full command listing\n");
    Print("\n");
    Print("Current player: " + to_string(partyNum + 1) + '\n', PartyColors[partyNum]);
    Print("Your gold: ");
    Print(to_string(game->players[partyNum].gold) + "\n", static_cast<int>(Color::Yellow));
    Print("\n");
}

string ConsoleController::Pad(string str, int size, char paddingChar){
    if (size > str.size())
        str.insert(str.size(), size - str.size(), paddingChar);
    return str;
}

vector<string> ConsoleController::ReadLine(){
    string str;
    getline(cin, str);
    istringstream ss(str);
    string word;
    vector<string> output;
    while(ss >> word){
        output.push_back(word);
    }
    return output;
}

void ConsoleController::Clear() const {
    system("cls");
}

bool ConsoleController::PerformCommand(){
    vector<string> strs = ConsoleController::ReadLine();
    if (strs.empty())
        return false;
    if (StrToCommand.find(strs[0]) == StrToCommand.end()) {
        Print("Unknown command: " + strs[0] + "\n");
        return false;
    }
    Unit* unit;
    int x, y;
    switch (StrToCommand[strs[0]]) {
        case Command::Help:
            Print(HelpText);
            return false;
        case Command::Clear:
            Redraw();
            return false;
        case Command::Skip:
            return true;
        case Command::Info:
            if (GetUnit(unit,strs,1,false))
                UnitInfo(*unit);
            return false;
        case Command::Die:
            if (GetUnit(unit,strs,1,true)) {
                unit->SelfDestruct();
                Redraw();
            }
            return false;
        case Command::Create:
            if (GetUnit(unit,strs,1,true)) {
                vector<UnitModuleType> modules;
                for (int i = 3; i < strs.size(); ++i) {
                    if (StrToModule.find(strs[i]) == StrToModule.end()) {
                        Print("Unknown module type: " + strs[i] + "\n");
                        return false;
                    }
                    modules.push_back(StrToModule[strs[i]]);
                }
                CreateAction(*unit,modules);
            }
            return false;
        case Command::Attack:
            if (GetUnit(unit,strs,1,true) && GetPosition(x,y,strs,3)){
                AttackAction(*unit, x, y);
            }
            return false;
        case Command::Go:
            if (GetUnit(unit,strs,1,true) && GetPosition(x,strs,3)){
                GoAction(*unit, x);
            }
            return false;
        case Command::Mine:
            if (GetUnit(unit,strs,1,true)){
                MineAction(*unit);
            }
            return false;
        default:
            Print("Unknown command: " + strs[0] + "\n");
            return false;
    }
}

bool ConsoleController::GetPosition(int& x, int& y, std::vector<std::string>& strs, int i0){
    if (i0 + 1 >= strs.size()){
        Print("Not enough arguments\n");
        return false;
    }
    try {
        x = stoi(strs[i0]);
    }
    catch(const invalid_argument& e){
        Print("Invalid type of " + to_string(i0 + 1) + " argument\n");
        return false;
    }
    try {
        y = stoi(strs[i0 + 1]);
    }
    catch(const invalid_argument& e){
        Print("Invalid type of " + to_string(i0 + 2) + " argument\n");
        return false;
    }
    --x;
    --y;
    if (!game->InWorld(x)){
        Print("Destination is out of this world\n");
        return false;
    }
    return true;
}

bool ConsoleController::GetPosition(int& x, std::vector<std::string>& strs, int i0){
    if (i0 >= strs.size()){
        Print("Not enough arguments\n");
        return false;
    }
    try {
        x = stoi(strs[i0]);
    }
    catch(const invalid_argument& e){
        Print("Invalid type of " + to_string(i0 + 1) + " argument\n");
        return false;
    }
    --x;
    if (!game->InWorld(x)){
        Print("Destination is out of this world\n");
        return false;
    }
    return true;
}

bool ConsoleController::GetUnit(Unit*& unit, std::vector<std::string>& strs, int i0, bool sameColor){
    int x,y;
    if (!GetPosition(x, y, strs, i0))
        return false;
    if (game->tiles[x].entities.size() <= y){
        Print("There is no units\n");
        return false;
    }
    unit = dynamic_cast<Unit*>(game->tiles[x].entities[y]);
    if (unit == nullptr)
        throw invalid_argument("Anything except class Unit isn't expected");
    if (sameColor && unit->Color() != partyNum){
        Print("Hey, it isn't your pawn!\n");
        return false;
    }
    return true;
}

void ConsoleController::UnitInfo(Unit& unit) const{
    Print("HP: " + to_string(unit.HP()) + "/" + to_string(unit.Stats().iStats.at(StatType::MaxHP)) + "\n");
    if (unit.Stats().bStats.at(StatType::Fabric))
        Print("Fabric\n");
    if (!unit.Stats().bStats.at(StatType::Immovable))
        Print("Movement: " + to_string(unit.MovePoints()) + "/" + to_string(unit.Stats().iStats.at(StatType::Speed)) + "\n");
    if (unit.Stats().bStats.at(StatType::CanAttack)){
        Print("Attacks: " + to_string(unit.AttackPoints()) + "/" + to_string(unit.Stats().iStats.at(StatType::AttackCount)) + "\n");
        Print("Damage: " + to_string(unit.Stats().iStats.at(StatType::Damage)) + "\n");
        Print("Range: " + to_string(unit.Stats().iStats.at(StatType::AttackRange)) + "\n");
    }
    if (unit.Stats().bStats.at(StatType::CanMine)){
        Print("Mine actions: " + to_string(unit.MinePoints()) + "/" + to_string(unit.Stats().iStats.at(StatType::MineCount)) + "\n");
        Print("Mine income: " + to_string(unit.Stats().iStats.at(StatType::MineSpeed)) + "\n");
    }
    if (unit.Stats().iStats.at(StatType::PassiveIncome) != 0)
        Print("Passive income: " + to_string(unit.Stats().iStats.at(StatType::PassiveIncome)) + "\n");
}

void ConsoleController::CreateAction(Unit& unit, std::vector<UnitModuleType>& modules){
    switch (unit.Create(modules)){
        case CreateResult::Done:
            Redraw();
            break;
        case CreateResult::TileOvercrowded:
            Print("Too many units here\n");
            break;
        case CreateResult::TooExpensive:
            Print("You haven't enough gold\n");
            break;
        case CreateResult::IncompatibleModules:
            Print("Modules incompatible\n");
            break;
        case CreateResult::CantCreate:
            Print("Unit don't know how to create\n");
            break;
    }
}

void ConsoleController::GoAction(Unit& unit, int x){
    switch (unit.Go(x)){
        case MoveResult::Done:
            Redraw();
            break;
        case MoveResult::TileOvercrowded:
            Print("There is not enough place\n");
            break;
        case MoveResult::UnitImmovable:
            Print("Unit is stationary\n");
            break;
        case MoveResult::PathBlocked:
            Print("Unit's way is blocked\n");
            break;
        case MoveResult::TileTooFar:
            Print("It's too far\n");
            break;
        case MoveResult::TileOutOfWorld:
            Print("You can't escape from this world\n");
            break;
    }
}

void ConsoleController::AttackAction(Unit& unit1, int x, int y){
    switch (unit1.Attack(x,y)){
        case AttackResult::Done:
            Redraw();
            break;
        case AttackResult::NoAttackPoints:
            Print("Unit exhausted\n");
            break;
        case AttackResult::TargetNotExist:
            Print("You can't hit emptiness\n");
            break;
        case AttackResult::TargetOutOfRange:
            Print("Unit is too shorthanded for it\n");
            break;
        case AttackResult::CantAttack:
            Print("Unit is pacifist\n");
            break;
    }
}

void ConsoleController::MineAction(Unit& unit){
    switch (unit.Mine()){
        case MineResult::Done:
            Redraw();
            break;
        case MineResult::NoMinePoints:
            Print("Unit exhausted\n");
            break;
        case MineResult::CantMine:
            Print("Unit has trypophobia\n");
            break;
    }
}

void ConsoleController::StaticInit(){
    HelpText = ConfigLoader::LoadHelp();
}