//
// Created by usuario on 20/8/19.
//

#include "EndGame.h"

#include "../GameManager.h"

EndGame::EndGame(GameManager *mgr) : Action(mgr) {}

void EndGame::run() {
    gameManager->endGame();
}