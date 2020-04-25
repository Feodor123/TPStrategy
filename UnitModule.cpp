#include "UnitModule.h"

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
        //forbidden.insert(UnitModule::Templates[m].incompatibilities.begin(),UnitModule::Templates[m].incompatibilities.end());
    }
    return true;
}

std::unordered_map<UnitModuleType, UnitModule> UnitModule::Templates {
        {UnitModuleType::Attack1,
                UnitModule(unordered_set<UnitModuleType>({
                                                                 UnitModuleType::Attack1,
                                                                 UnitModuleType::Attack2,
                                                                 UnitModuleType::Attack3,
                                                         }),
                           unordered_map<StatType, int>{
                                   {StatType::Damage, 10},
                                   {StatType::Cost, 50},
                           },
                           unordered_map<StatType, bool>{
                                   {CanAttack, true}
                           }
                )
        },
        {UnitModuleType::Attack2,
                UnitModule(unordered_set<UnitModuleType>({
                                                                 UnitModuleType::Attack1,
                                                                 UnitModuleType::Attack2,
                                                                 UnitModuleType::Attack3,
                                                         }),
                           unordered_map<StatType, int>{
                                   {StatType::Damage, 15},
                                   {StatType::Cost, 100},
                           },
                           unordered_map<StatType, bool>{
                                   {CanAttack, true}
                           }
                )
        },
        {UnitModuleType::Attack3,
                UnitModule(unordered_set<UnitModuleType>({
                                                                 UnitModuleType::Attack1,
                                                                 UnitModuleType::Attack2,
                                                                 UnitModuleType::Attack3,
                                                         }),
                           unordered_map<StatType, int>{
                                   {StatType::Damage, 20},
                                   {StatType::Cost, 150},
                           },
                           unordered_map<StatType, bool>{
                                   {CanAttack, true}
                           }
                )
        },
        {UnitModuleType::Mine1,
                UnitModule(unordered_set<UnitModuleType>({
                                                                 UnitModuleType::Mine1,
                                                                 UnitModuleType::Mine2,
                                                                 UnitModuleType::Mine3,
                                                         }),
                           unordered_map<StatType, int>{
                                   {StatType::MineSpeed, 10},
                                   {StatType::Cost, 50},
                           },
                           unordered_map<StatType, bool>{
                           }
                )
        },
        {UnitModuleType::Mine2,
                UnitModule(unordered_set<UnitModuleType>({
                                                                 UnitModuleType::Mine1,
                                                                 UnitModuleType::Mine2,
                                                                 UnitModuleType::Mine3,
                                                         }),
                           unordered_map<StatType, int>{
                                   {StatType::MineSpeed, 15},
                                   {StatType::Cost, 100},
                           },
                           unordered_map<StatType, bool>{
                           }
                )
        },
        {UnitModuleType::Mine3,
                UnitModule(unordered_set<UnitModuleType>({
                                                                 UnitModuleType::Mine1,
                                                                 UnitModuleType::Mine2,
                                                                 UnitModuleType::Mine3,
                                                         }),
                           unordered_map<StatType, int>{
                                   {StatType::MineSpeed, 20},
                                   {StatType::Cost, 150},
                           },
                           unordered_map<StatType, bool>{
                           }
                )
        },
};
