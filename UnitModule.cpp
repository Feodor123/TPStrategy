#include "UnitModule.h"
#include "UnitModuleStore.h"

using namespace std;

UnitModule::UnitModule(unordered_set<UnitModuleType> incompatibilities,
        unordered_map<StatType, int> iValues,
        unordered_map<StatType, bool> bValues)
: iValues(iValues), bValues(bValues), incompatibilities(incompatibilities){}

bool UnitModule::AreCompatible(std::vector<UnitModuleType> &modules) {
    unordered_set<UnitModuleType> forbidden;
    for (auto m : modules){
        if (forbidden.count(m) != 0)
            return false;
        forbidden.insert(UnitModuleStore::Instance().templates.at(m).incompatibilities.begin(),
                UnitModuleStore::Instance().templates.at(m).incompatibilities.end());
    }
    return true;
}
