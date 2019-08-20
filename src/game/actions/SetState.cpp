//
// Created by usuario on 20/8/19.
//

#include "SetState.h"
#include "../GameManager.h"

SetState::SetState(GameManager *mgr, std::string item, std::string state) : Action(mgr){
    parameters["item"] = item;
    parameters["state"] = state;
}

void SetState::run() {
    gameManager->setState(parameters["item"], parameters["state"]);
}