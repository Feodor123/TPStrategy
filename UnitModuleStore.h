#ifndef TPSTRATEGY_UNITMODULESTORE_H
#define TPSTRATEGY_UNITMODULESTORE_H

#include "UnitModule.h"
#include "string"
//Singleton; allow access to provided modules
class UnitModuleStore {
public:
    static const UnitModuleStore& Instance();
    std::unordered_map<UnitModuleType, UnitModule> templates;
private:
    UnitModuleStore();
    void LoadModules(std::string path);
    static UnitModuleStore instance;
    static bool isInstance;
};


#endif
