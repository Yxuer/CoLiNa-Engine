#include <iostream>
#include "game/GameManager.h"

int main() {

    GameManager *game = new GameManager();

    game->loadXML("test.txt");
    game->startGame();

    delete game;
}