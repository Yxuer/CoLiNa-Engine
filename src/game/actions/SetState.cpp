//
// Created by usuario on 20/8/19.
//

#include "SetState.h"
#include "../GameManager.h"

SetState::SetState(GameManager *mgr) : Action(mgr){
    listOfParameterNames.emplace_back("item");
    listOfParameterNames.emplace_back("state");
}

void SetState::run() {
    gameManager->getArea(gameManager->getCurrentLocation())
               ->getItem(parameters["item"])
               ->setState(parameters["state"]);
}