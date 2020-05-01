#ifndef TPSTRATEGY_CONFIGLOADER_H
#define TPSTRATEGY_CONFIGLOADER_H

#include "string"
#include "UnitModule.h"
//load data from configs
class ConfigLoader {
private:
    static const std::string CONFIG_PATH;

    static std::vector<std::string> Split(std::string line);
public:
    static std::string LoadHelp();

    static std::unordered_map<UnitModuleType, UnitModule> LoadModules();

    static std::unordered_map<std::string, UnitModuleType> StrToModuleType;

    static std::unordered_map<std::string, StatType> StrToStatType;

    static void ThrowUnknownWordException(const std::string& filename, const std::string& word);
};


#endif //TPSTRATEGY_CONFIGLOADER_H
