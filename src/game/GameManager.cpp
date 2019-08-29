//
// Created by usuario on 19/8/19.
//

#include "GameManager.h"
#include "util/GameExceptions.h"
#include "actions/Action.h"

#include <iostream>
#include <sstream>

#ifndef XMLCheckResult
    #define XMLCheckResult(a_eResult) if (a_eResult != tinyxml2::XML_SUCCESS) { throw XMLQueryError(); }
#endif

GameManager* GameManager::instance = 0;

/*Implementation for the Singleton pattern: returns the unique GameManager instance*/
GameManager* GameManager::getInstance() {

    if (instance == 0) {
        instance = new GameManager();
        Action::gameManager = instance;
    }

    return instance;
}

/*GameManager constructor*/
GameManager::GameManager() {
    finishGame = false;
    location = "";
}

/*Deletes all areas, items, commands and actions of the game*/
void GameManager::erase() {
    for (auto area : areaList) {
        delete area.second;
    }
}

/*Loads the XML game file into the proper game objects, given the filename of
 * the file to load*/
void GameManager::loadXML(const std::string &filename) {

    std::cout << "Loading game file " << filename << "\n";

    // Load XML game file
    tinyxml2::XMLDocument xmlDoc;
    tinyxml2::XMLError eResult = xmlDoc.LoadFile(filename.c_str());
    if (eResult != tinyxml2::XML_SUCCESS) {
        throw FileLoadError();
    }

    // Get first XML node and check if it is properly constructed
    tinyxml2::XMLNode *root = xmlDoc.FirstChild();
    if (root == nullptr || std::string(root->Value()) != "Game") {
        throw InvalidXMLError();
    }

    // Start reading game information itself: areas, their items, their states,
    // their actions and their primitives
    tinyxml2::XMLNode *areaReader = root->FirstChild();
    if (areaReader == nullptr) {
        throw InvalidAreaError();
    }

    // Area reading loop
    while (areaReader != nullptr) {
        if (std::string(areaReader->Value()) != "Area") {
            throw InvalidAreaError();
        }
        std::cout << "Reading area\n";

        Area *areaBeingBuilt;
        const char * areaName, *areaDescription;
        bool startingArea;
        std::map<std::string, Item*>* itemList;
        auto areaAttrsReader = dynamic_cast<tinyxml2::XMLElement*>(areaReader);

        eResult = areaAttrsReader->QueryStringAttribute("name", &areaName);
        XMLCheckResult(eResult);

        eResult = areaAttrsReader->QueryStringAttribute("text", &areaDescription);
        XMLCheckResult(eResult);

        eResult = areaAttrsReader->QueryBoolAttribute("startingZone", &startingArea);
        XMLCheckResult(eResult);

        // Check if the starting area is unique
        if (startingArea) {
            if (!location.empty()) {
                throw MultipleStartingAreasError();
            }
            location = areaName;
        }

        // Check if the area name is duplicated
        if (areaList.find(areaName) != areaList.end()) {
            throw DuplicatedElementError("Area", areaName);
        }

        itemList = readAreaItems(areaReader);

        areaBeingBuilt = new Area(itemList, areaName, areaDescription, startingArea);
        areaList.insert(std::make_pair(std::string(areaName), areaBeingBuilt));

        areaReader = areaReader->NextSibling();
    }
}

/*Auxiliary function to read the items in a certain area from the XML file, given the
 * reference to the current area being read (XML)*/
std::map<std::string, Item*>* GameManager::readAreaItems(tinyxml2::XMLNode *areaRef) {

    auto itemList = new std::map<std::string, Item*>();
    tinyxml2::XMLError eResult;

    tinyxml2::XMLNode *itemReader = areaRef->FirstChild();
    if (itemReader == nullptr) {
        throw InvalidItemError();
    }

    // Item reading loop
    while (itemReader != nullptr) {
        if (std::string(itemReader->Value()) != "Item") {
            throw InvalidItemError();
        }
        std::cout << "  Reading item\n";

        Item* itemBeingBuilt;
        const char *name, *state;
        std::map<std::string, std::map<std::string, std::vector<Action*>*>*>* actionsPerState;
        auto itemAttrsReader = dynamic_cast<tinyxml2::XMLElement*>(itemReader);

        eResult = itemAttrsReader->QueryStringAttribute("name", &name);
        XMLCheckResult(eResult);

        eResult = itemAttrsReader->QueryStringAttribute("state", &state);
        XMLCheckResult(eResult);

        // Check if the item name is duplicated
        if (itemList->find(name) != itemList->end()) {
            throw DuplicatedElementError("Item", name);
        }

        actionsPerState = readItemStates(itemReader);

        itemBeingBuilt = new Item(actionsPerState, name, state);
        itemList->insert(std::make_pair(name, itemBeingBuilt));

        itemReader = itemReader->NextSibling();
    }

    return itemList;
}

/*Auxiliary function to read the commands of a certain item from the XML file, given the
 * reference to the current item being read (XML)*/
std::map<std::string, std::map<std::string, std::vector<Action*>*>*>* GameManager::readItemStates(tinyxml2::XMLNode *itemRef) {

    auto stateList = new std::map<std::string, std::map<std::string, std::vector<Action*>*>*>();
    std::map<std::string, std::vector<Action*>*> *commandActions;
    tinyxml2::XMLError eResult;

    tinyxml2::XMLNode *stateReader = itemRef->FirstChild();
    if (stateReader == nullptr) {
        throw InvalidStateError();
    }

    // State reading loop
    while (stateReader != nullptr) {
        if (std::string(stateReader->Value()) != "State") {
            throw InvalidStateError();
        }
        std::cout << "      Reading state\n";

        const char * stateName;
        auto stateAttrsReader = dynamic_cast<tinyxml2::XMLElement*>(stateReader);

        eResult = stateAttrsReader->QueryStringAttribute("name", &stateName);
        XMLCheckResult(eResult);

        // Check if the state name is duplicated
        if (stateList->find(stateName) != stateList->end()) {
            throw DuplicatedElementError("State", stateName);
        }

        commandActions = new std::map<std::string, std::vector<Action*>*>();
        tinyxml2::XMLNode *commandReader = stateReader->FirstChild();
        if (commandReader == nullptr) {
            throw InvalidCommandError();
        }
        // Command reading loop
        while (commandReader != nullptr) {
            if (std::string(commandReader->Value()) != "Command") {
                throw InvalidCommandError();
            }
            std::cout << "          Reading command\n";

            const char * commandName;
            std::vector<Action*>* actionListPerState;
            auto commandAttrsReader = dynamic_cast<tinyxml2::XMLElement*>(commandReader);

            eResult = commandAttrsReader->QueryStringAttribute("name", &commandName);
            XMLCheckResult(eResult);

            // Check if the state name is duplicated
            if (commandActions->find(commandName) != commandActions->end()) {
                throw DuplicatedElementError("Command", commandName);
            }

            actionListPerState = readCommandActions(commandReader);

            commandActions->insert(std::make_pair(commandName, actionListPerState));

            commandReader = commandReader->NextSibling();
        }

        stateList->insert(std::make_pair(stateName, commandActions));

        stateReader = stateReader->NextSibling();
    }

    return stateList;
}

/*Auxiliary function to read the actions of a certain command from the XML file, given the
 * reference to the current command being read (XML)*/
std::vector<Action*>* GameManager::readCommandActions(tinyxml2::XMLNode *commandRef) {
    auto actionList = new std::vector<Action*>();

    tinyxml2::XMLNode *actionReader = commandRef->FirstChild();
    tinyxml2::XMLError eResult;
    if (actionReader == nullptr) {
        throw InvalidActionError();
    }
    // Action reading loop
    while (actionReader != nullptr) {
        if (std::string(actionReader->Value()) != "Action") {
            throw InvalidActionError();
        }
        std::cout << "              Reading action\n";

        Action* actionBeingBuilt;
        const char * actionName, *paramRead;
        auto actionAttrsReader = dynamic_cast<tinyxml2::XMLElement*>(actionReader);

        eResult = actionAttrsReader->QueryStringAttribute("name", &actionName);
        XMLCheckResult(eResult);

        // Instantiate specific action given (if it exists)
        if (Action::listOfActions.find(actionName) == Action::listOfActions.end()) {
            throw XMLUnknownActionError();
        }

        actionBeingBuilt = Action::make_action(actionName);
        std::vector<std::string> paramList = actionBeingBuilt->getListOfParameterNames();

        for (auto str : paramList) {
            eResult = actionAttrsReader->QueryStringAttribute(str.c_str(), &paramRead);
            XMLCheckResult(eResult);
            actionBeingBuilt->setParameter(str.c_str(), paramRead);
        }

        actionList->push_back(actionBeingBuilt);

        actionReader = actionReader->NextSibling();
    }

    return actionList;
}

/*Game main loop*/
void GameManager::startGame() {

    std::vector<std::string> *input = nullptr;

    while (!finishGame) {
        input = getCommand();
        std::cout << "\n";
        runCommand(input);
        delete input;
    }
}

/*Reads a command from the player and verifies its structure*/
std::vector<std::string>* GameManager::getCommand() {

    std::vector<std::string> *input = nullptr;
    bool repeatParsing;

    do {
        try {
            if (input != nullptr) {
                delete input;
            }

            repeatParsing = true;
            std::cout << "\n>>> ";
            input = parseInput();

            if (input->size() > 2) { throw TooManyWordsException();}
            if (input->size() == 1 && input->front().compare("examine")) { throw InvalidExamineException();}

            repeatParsing = false;

        } catch (const LesserException &e) {
            std::cout << e.what() << "\n";
        }
    } while(repeatParsing);

    return input;
}

/*Auxiliary function to read user input and separate it by whitespaces*/
std::vector<std::string>* GameManager::parseInput() {
    std::string input;
    std::vector<std::string> *splitInput = new std::vector<std::string>();

    std::getline(std::cin, input);

    std::istringstream iss(input);

    for(std::string s; iss >> s; ) {
        splitInput->push_back(s);
    }

    return splitInput;
}

/*Runs the command given by the player*/
void GameManager::runCommand(std::vector<std::string> *command) {
    // 1-word commands
    if (command->size() == 1) {
        std::cout << "Running a 1-word command.\n";
    }

    else if (command->size() == 2) {
        try {
            auto currentArea = areaList.find(location);

            if (currentArea == areaList.end()) {
                throw UnknownLocationError();
            }

            auto areaItem = currentArea->second->getItem(command->at(1));
            if (areaItem == nullptr) {
                throw UnknownItemException();
            }

            areaItem->act(command->at(0));
        } catch (const LesserException& e) {
            std::cout << e.what();
        }
    }
}

/*Sets the finishGame flag to the given boolean value*/
void GameManager::setEndGame(bool end) {
    finishGame = end;
}

/*Returns the area whose name is the one given to the function*/
Area* GameManager::getArea(const std::string &name) {
    if (areaList.find(name) == areaList.end()) {
        return nullptr;
    }
    return areaList[name];
}

/*Returns the current location of the player*/
const std::string& GameManager::getCurrentLocation() {
    return location;
}

/*Sets the current location of the player*/
void GameManager::setCurrentLocation(const std::string &newLoc) {
    location = newLoc;

    if (areaList.find(location) == areaList.end()) {
        throw UnknownLocationError();
    }
}