//
// Created by usuario on 19/8/19.
//

#include "GameManager.h"
#include "util/GameExceptions.h"

#include <iostream>
#include <sstream>

GameManager::GameManager() {
    finishGame = false;
}

GameManager::~GameManager() {

}

void GameManager::loadXML(const std::string &filename) {

    std::cout << "Loading game file " << filename;
}

void GameManager::startGame() {

    std::vector<std::string> *input = nullptr;

    while (!finishGame) {
        input = getCommand();

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

            if (input->size() > 2) { throw tooManyWordsException;}
            if (input->size() == 1 && input->front().compare("examine")) { throw invalidExamineException;}

            repeatParsing = false;

        } catch (const TooManyWordsException &e) {
            std::cout << e.what() << "\n";
        } catch (const InvalidExamineException &e) {
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