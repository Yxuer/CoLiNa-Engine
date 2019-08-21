//
// Created by usuario on 20/8/19.
//

#include "Print.h"

#include "../GameManager.h"

Print::Print() : Action(){
    listOfParameterNames.emplace_back("text");
}

void Print::run() {
    printf("%s", parameters["text"].c_str());
}