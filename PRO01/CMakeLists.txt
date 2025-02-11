cmake_minimum_required(VERSION 3.21)
project(PRO01)

set(CMAKE_CXX_STANDARD 17)

add_executable(PRO01 main.cpp Creature.cpp Creature.h Values.cpp Values.h SpecialAbility.cpp SpecialAbility.h Effect.cpp Effect.h Team.cpp Team.h Help.cpp Help.h Battle.cpp Battle.h Run.cpp Run.h CustomExceptions.h)
