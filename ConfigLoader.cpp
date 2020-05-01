#include "ConfigLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

unordered_map<std::string, UnitModuleType> ConfigLoader::StrToModuleType{
        {"Attack1", UnitModuleType::Attack1},
        {"Attack2", UnitModuleType::Attack2},
        {"Attack3", UnitModuleType::Attack3},
        {"Mine1", UnitModuleType::Mine1},
        {"Mine2", UnitModuleType::Mine2},
        {"Mine3", UnitModuleType::Mine3},
        {"Building", UnitModuleType::Building},
};

unordered_map<std::string, StatType> ConfigLoader::StrToStatType{
        {"Cost", StatType::Cost},
        {"Fabric", StatType::Fabric},
        {"PassiveIncome", StatType::PassiveIncome},
        {"MineSpeed", StatType::MineSpeed},
        {"MineCount", StatType::MineCount},
        {"CanMine", StatType::CanMine},
        {"AttackRange", StatType::AttackRange},
        {"Damage", StatType::Damage},
        {"AttackCount", StatType::AttackCount},
        {"CanAttack", StatType::CanAttack},
        {"Speed", StatType::Speed},
        {"Immovable", StatType::Immovable},
        {"MaxHP", StatType::MaxHP},
};

const string ConfigLoader::CONFIG_PATH  = "../configs/";

std::string ConfigLoader::LoadHelp() {
    string text;
    ifstream stream;
    try {
        stream.open(CONFIG_PATH + "Help.txt");
        text = string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
        stream.close();
    }
    catch (const exception &e) {
        stream.close();
        throw;
    }
    return text;
};

std::unordered_map<UnitModuleType, UnitModule> ConfigLoader::LoadModules(){
    string filename = "Modules.txt";
    std::unordered_map<UnitModuleType, UnitModule> modules;
    ifstream stream;
    try {
        stream.open(CONFIG_PATH + filename);
        UnitModule module;
        UnitModuleType type = UnitModuleType::None;
        string line;
        while (std::getline(stream, line))
        {
            vector<string> strs = Split(line);
            if (!strs.empty()){
                if (strs[0] == "Module"){
                    if (type != UnitModuleType::None) {
                        modules.insert(make_pair(type, module));
                        type = UnitModuleType::None;
                        module = UnitModule();
                    }
                    if (StrToModuleType.find(strs[1]) == StrToModuleType.end())
                        ThrowUnknownWordException(strs[1], filename);
                    type = StrToModuleType[strs[1]];
                }
                else if (strs[0] == "Int"){
                    if (StrToStatType.find(strs[1]) == StrToStatType.end())
                        ThrowUnknownWordException(strs[1], filename);
                    module.iValues[StrToStatType[strs[1]]] = stoi(strs[2]);
                }
                else if (strs[0] == "Bool"){
                    if (StrToStatType.find(strs[1]) == StrToStatType.end())
                        ThrowUnknownWordException(strs[1], filename);
                    module.bValues[StrToStatType[strs[1]]] = (strs[2] == "true");
                }
                else if (strs[0] == "Incomp"){
                    for (int i = 1;i < strs.size();++i){
                        if (StrToModuleType.find(strs[i]) == StrToModuleType.end())
                            ThrowUnknownWordException(strs[i], filename);
                        module.incompatibilities.insert(StrToModuleType[strs[i]]);
                    }
                }
                else
                    ThrowUnknownWordException(strs[0], filename);
            }
            if (type != UnitModuleType::None)
                modules.insert(make_pair(type, module));
        }
        stream.close();
    }
    catch (const exception &e) {
        stream.close();
        throw;
    }
    return modules;
}

vector<string> ConfigLoader::Split(std::string line){
    istringstream ss(line);
    string word;
    vector<string> output;
    while(ss >> word){
        output.push_back(word);
    }
    return output;
};

void ConfigLoader::ThrowUnknownWordException(const std::string& word, const std::string& filename){
    throw invalid_argument("Unknown keyword \"" + word + "\" in " + filename);
}