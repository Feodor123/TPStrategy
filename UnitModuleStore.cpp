#include "UnitModuleStore.h"
#include "ConfigLoader.h"

bool UnitModuleStore::isInstance = false;

UnitModuleStore UnitModuleStore::instance;

const UnitModuleStore& UnitModuleStore::Instance(){
    if (!isInstance) {
        instance = UnitModuleStore();
        isInstance = true;
    }
    return instance;
}

UnitModuleStore::UnitModuleStore() {
    LoadModules("../configs/Modules");
}

void UnitModuleStore::LoadModules(std::string path){
    templates = ConfigLoader::LoadModules();
}