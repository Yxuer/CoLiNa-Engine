//
// Created by usuario on 19/8/19.
//

#include "GameManager.h"
#include "util/GameExceptions.h"
#include "util/TinyXML2/tinyxml2.h"

#include <iostream>
#include <sstream>

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

        tinyxml2::XMLNode *itemReader = areaReader->FirstChild();
        if (itemReader == nullptr) {
            throw InvalidItemError();
        }

        // Item reading loop
        while (itemReader != nullptr) {
            if (std::string(itemReader->Value()) != "Item") {
                throw InvalidItemError();
            }
            std::cout << "  Reading item\n";

            tinyxml2::XMLNode *stateReader = itemReader->FirstChild();
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

            itemReader = itemReader->NextSibling();
        }

        areaReader = areaReader->NextSibling();
    }
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

void GameManager::endGame() {
    finishGame = true;
}

void GameManager::print(const std::string &text) {
    printf("%s", text.c_str());
}

void GameManager::setState(const std::string &item, const std::string &state) {
    // TODO Complete
    areaList["location"]->getItem(item);
}