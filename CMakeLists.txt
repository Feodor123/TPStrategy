cmake_minimum_required(VERSION 3.13)
project(TPStrategy)

set(CMAKE_CXX_STANDARD 14)

add_executable(TPStrategy main.cpp cmake-build-debug/Game.cpp cmake-build-debug/Game.h cmake-build-debug/Session.cpp cmake-build-debug/Session.h cmake-build-debug/Entity.cpp cmake-build-debug/Entity.h cmake-build-debug/Unit.cpp cmake-build-debug/Unit.h cmake-build-debug/Building.cpp cmake-build-debug/Building.h cmake-build-debug/Fortress.cpp cmake-build-debug/Fortress.h)