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
    // Map of areas in the game, mapped by area name
    std::map<std::string, Area*> areaList;

    // Inventory the player has
    std::map<std::string, unsigned int> playerInventory;

    // Current location of the player
    std::string location;

    // Flag to indicate if the game has finished
    bool finishGame;

    // List of 1-word commands
    std::map<std::string, std::vector<Action*>*> oneWordCommandList;

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

    Area* getArea(const std::string &name);
    void setEndGame(bool end);

    const std::string& getCurrentLocation();
    void setCurrentLocation(const std::string& newLoc);
};

#endif //UNTITLED_GAMEMANAGER_H
