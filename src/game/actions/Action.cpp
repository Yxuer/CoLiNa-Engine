//
// Created by usuario on 19/8/19.
//

#include "Action.h"
#include "../GameManager.h"

Action::Action(GameManager *manager) {
    gameManager = manager;
}

Action::~Action() {}

void Action::run() {}