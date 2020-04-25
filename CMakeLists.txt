cmake_minimum_required(VERSION 3.13)
project(TPStrategy)

set(CMAKE_CXX_STANDARD 14)

add_executable(TPStrategy main.cpp Game.cpp Game.h Entity.cpp Entity.h Unit.cpp Unit.h UnitModule.cpp UnitModule.h Server.cpp Server.h Controller.cpp Controller.h ActionResult.h StatType.h UnitStats.cpp UnitStats.h ConsoleController.cpp ConsoleController.h)

set(CMAKE_EXE_LINKER_FLAGS "-static")