//
// Created by usuario on 29/08/19.
//

#include "ChangeArea.h"
#include "../GameManager.h"

ChangeArea::ChangeArea() : Action() {
    listOfParameterNames.emplace_back("areaName");
}

void ChangeArea::run() {
    gameManager->setCurrentLocation(parameters["areaName"]);
}