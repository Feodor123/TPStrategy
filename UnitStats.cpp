#include "UnitStats.h"

using namespace std;

UnitStats::UnitStats(const unordered_map<StatType, int>& iVals, const unordered_map<StatType, bool>& bVals) : iStats(iVals), bStats(bVals) {}

void UnitStats::AddModules(const vector<UnitModuleType>& modules){
    for (auto m : modules){
        for (pair<const StatType, int> p : UnitModule::Templates[m].iValues){
            iStats[p.first] += p.second;
        }
        for (auto p : UnitModule::Templates[m].bValues){
            bStats[p.first] |= p.second;
        }
    }
}