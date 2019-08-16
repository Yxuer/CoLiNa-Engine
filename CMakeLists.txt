cmake_minimum_required(VERSION 3.14)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled src/main.cpp
                            src/game/GameManager.h
                            src/game/Area.h
                            src/game/Item.h
                                src/game/actions/Action.h)