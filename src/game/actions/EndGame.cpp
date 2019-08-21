//
// Created by usuario on 20/8/19.
//

#include "EndGame.h"

#include "../GameManager.h"

EndGame::EndGame() : Action() {}

void EndGame::run() {
    gameManager->setEndGame(true);
}