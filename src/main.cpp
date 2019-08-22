#include <iostream>
#include <limits>
#include "game/GameManager.h"
#include "game/util/GameExceptions.h"

int main() {

    bool keepAskingForFile = true;
    std::string filename;

    std::cout << "Welcome to the COmmand-LIne-NArration engine!\n"
                 "Made by Yxuer because he was bored.\n"
                 "Please write the name of the game file you wish to load.\n"
                 ">>> ";

    do {
        std::cin >> filename;
        std::cout << "\n";
        if (FILE *file = fopen(filename.c_str(), "r")) {
            fclose(file);
            keepAskingForFile = false;
        } else {
            std::cout << "That file does not exist. Please, write\n"
                         "the name of an existing game file.\n"
                         ">>> ";
        }
    } while(keepAskingForFile);

    GameManager *game = GameManager::getInstance();

    try {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        game->loadXML(filename);
        game->startGame();
    } catch (FatalException &e) {
        std::cout << e.what();
    }

    game->erase();
}