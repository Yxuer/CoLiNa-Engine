//
// Created by usuario on 19/8/19.
//

#include "GameManager.h"
#include "util/GameExceptions.h"

#include <iostream>
#include <sstream>

#ifndef XMLCheckResult
    #define XMLCheckResult(a_eResult) if (a_eResult != tinyxml2::XML_SUCCESS) { throw XMLQueryError(); }
#endif

GameManager::GameManager() {
    finishGame = false;
    listOfActions = {"setState", "print", "endGame"};
}

GameManager::~GameManager() {

}

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

        itemList = readAreaItems(areaReader);

        areaBeingBuilt = new Area(itemList, areaName, areaDescription, startingArea);
        areaList.insert(std::make_pair(std::string(areaName), areaBeingBuilt));

        areaReader = areaReader->NextSibling();
    }
}

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
        std::map<std::string, std::map<std::string, Action**>>* actionsPerState;
        auto itemAttrsReader = dynamic_cast<tinyxml2::XMLElement*>(itemReader);

        eResult = itemAttrsReader->QueryStringAttribute("name", &name);
        XMLCheckResult(eResult);

        eResult = itemAttrsReader->QueryStringAttribute("state", &state);
        XMLCheckResult(eResult);

        actionsPerState = readItemStates(itemReader);

        itemBeingBuilt = new Item(actionsPerState, name, state);
        itemList->insert(std::make_pair(name, itemBeingBuilt));

        itemReader = itemReader->NextSibling();
    }

    return itemList;
}

std::map<std::string, std::map<std::string, Action**>>* GameManager::readItemStates(tinyxml2::XMLNode *itemRef) {

    auto stateList = new std::map<std::string, std::map<std::string, Action**>>();

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

            tinyxml2::XMLNode *actionReader = commandReader->FirstChild();
            if (actionReader == nullptr) {
                throw InvalidActionError();
            }
            // Action reading loop
            while (actionReader != nullptr) {
                if (std::string(actionReader->Value()) != "Action") {
                    throw InvalidActionError();
                }
                std::cout << "              Reading action\n";

                actionReader = actionReader->NextSibling();
            }

            commandReader = commandReader->NextSibling();
        }

        stateReader = stateReader->NextSibling();
    }

    return stateList;
}

std::vector<Action*>* GameManager::readCommandActions(tinyxml2::XMLNode *commandRef) {
    auto actionList = new std::vector<Action*>();

    return actionList;
}

void GameManager::startGame() {

    std::vector<std::string> *input = nullptr;

    while (!finishGame) {
        input = getCommand();
        std::cout << "\n";
        runCommand(input);
        delete input;
    }
}

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

void GameManager::runCommand(std::vector<std::string> *command) {
    // 1-word commands
    if (command->size() == 1) {
        std::cout << "Running a 1-word command.\n";
    }
    else if (command->size() == 2) {
        std::cout << "Running a regular command.\n";
    }
}

void GameManager::setEndGame(bool end) {
    finishGame = end;
}

Area* GameManager::getArea(std::string name) {
    return areaList[name];
}

const std::string& GameManager::getCurrentLocation() {
    return location;
}