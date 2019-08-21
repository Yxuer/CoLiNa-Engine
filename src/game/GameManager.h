//
// Created by luis on 16/8/19.
//

#ifndef UNTITLED_GAMEMANAGER_H
#define UNTITLED_GAMEMANAGER_H

#include "Area.h"
#include "util/TinyXML2/tinyxml2.h"

#include <map>
#include <vector>
#include <set>

class GameManager {

private:
    std::map<std::string, Area*> areaList;
    std::map<std::string, unsigned int> playerInventory;
    std::string location;
    bool finishGame;

    // Singleton implementation
    static GameManager *instance;
    GameManager();

    std::vector<std::string> *getCommand();
    std::vector<std::string> *parseInput();
    void runCommand(std::vector<std::string> *command);

    std::map<std::string, Item*>* readAreaItems(tinyxml2::XMLNode* areaRef);
    std::map<std::string, std::map<std::string, std::vector<Action*>*>*>* readItemStates(tinyxml2::XMLNode* itemRef);
    std::vector<Action*>* readCommandActions(tinyxml2::XMLNode* commandRef);

public:
    // Singleton implementation
    static GameManager* getInstance();

    void erase();

    void loadXML(const std::string& filename);
    void startGame();

    void addToInventory(const std::string& itemToAdd);
    void removeFromInventory(const std::string& itemToDelete);
    bool checkInventory(const std::string& itemToCheck);

    Area* getArea(std::string name);
    void setEndGame(bool end);

    const std::string& getCurrentLocation();
};

#endif //UNTITLED_GAMEMANAGER_H
