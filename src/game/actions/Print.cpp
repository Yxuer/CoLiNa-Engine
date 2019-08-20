//
// Created by usuario on 20/8/19.
//

#include "Print.h"

#include "../GameManager.h"

Print::Print(GameManager *mgr, std::string text) : Action(mgr){
    parameters["text"] = text;
}

void Print::run() {
    gameManager->print(parameters["text"]);
}