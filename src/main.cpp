#include <iostream>
#include "game/GameManager.h"
#include "game/util/GameExceptions.h"

int main() {

    GameManager *game = new GameManager();

    try {
        game->loadXML("test.xml");
        game->startGame();
    } catch (FatalException &e) {
        std::cout << e.what();
    }

    delete game;
}