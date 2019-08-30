//
// Created by usuario on 30/08/19.
//

#include "Examine.h"
#include "../GameManager.h"

Examine::Examine() : Action() {}

void Examine::run() {
    gameManager->getArea(gameManager->getCurrentLocation())->examine();
}