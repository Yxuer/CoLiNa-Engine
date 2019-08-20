cmake_minimum_required(VERSION 3.14)
project(CoLiNa-Engine)

set(CMAKE_CXX_STANDARD 14)

add_executable(CoLiNa-Engine src/main.cpp
                                src/game/GameManager.h
                                src/game/Area.h
                                src/game/Item.h
                                    src/game/actions/Action.h
                                    src/game/actions/Action.cpp

                                    src/game/util/GameExceptions.h

                                        src/game/util/TinyXML2/tinyxml2.h
                                        src/game/util/TinyXML2/tinyxml2.cpp

                                src/game/GameManager.cpp
                                src/game/Area.cpp
                                src/game/Item.cpp
        src/game/actions/SetState.cpp src/game/actions/SetState.h src/game/actions/Print.cpp src/game/actions/Print.h src/game/actions/EndGame.cpp src/game/actions/EndGame.h)