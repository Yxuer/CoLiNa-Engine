//
// Created by usuario on 20/8/19.
//

#include "SetState.h"
#include "../GameManager.h"
#include "../util/GameExceptions.h"

SetState::SetState() : Action(){
    listOfParameterNames.emplace_back("item");
    listOfParameterNames.emplace_back("state");
}

void SetState::run() {
    Item *itemToSet = gameManager->getArea(gameManager->getCurrentLocation())
                                 ->getItem(parameters["item"]);

    if (itemToSet == nullptr) {
        throw UnknownItemError();
    }

    itemToSet->setState(parameters["state"]);
}