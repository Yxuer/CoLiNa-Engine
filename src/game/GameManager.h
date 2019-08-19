//
// Created by luis on 16/8/19.
//

#ifndef UNTITLED_GAMEMANAGER_H
#define UNTITLED_GAMEMANAGER_H

#include "Area.h"

#include <map>
#include <vector>

class GameManager {

private:
    std::map<std::string, Area> areaList;
    std::map<std::string, unsigned int> playerInventory;
    std::string location;
    bool finishGame;

    std::vector<std::string> *getCommand();
    std::vector<std::string> *parseInput();
    void runCommand(std::vector<std::string> *command);

public:
    GameManager();
    ~GameManager();

    void loadXML(const std::string& filename);
    void startGame();

    void addToInventory(const std::string& itemToAdd);
    void removeFromInventory(const std::string& itemToDelete);
    bool checkInventory(const std::string& itemToCheck);
};

#endif //UNTITLED_GAMEMANAGER_H
