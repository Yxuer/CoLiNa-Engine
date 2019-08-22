//
// Created by usuario on 19/8/19.
//

#include "Action.h"
#include "../GameManager.h"

#include "EndGame.h"
#include "SetState.h"
#include "Print.h"

GameManager* Action::gameManager = nullptr;
std::set<std::string> Action::listOfActions = {"setState", "print", "endGame"};

Action::Action(){}

Action::~Action() {}

/*Action subclass factory method*/
Action* Action::make_action(const std::string &actionName) {
    if (std::string(actionName) == "setState") {
        return new SetState();
    }
    else if (std::string(actionName) == "endGame") {
        return new EndGame();
    }
    else if (std::string(actionName) == "print") {
        return new Print();
    }
}

/*Returns the list of parameter names for this specific action*/
const std::vector<std::string>& Action::getListOfParameterNames() {
    return listOfParameterNames;
}

/*Sets the value of a certain parameter in this specific action*/
void Action::setParameter(const std::string &parameter, const std::string &value) {
    parameters[parameter] = value;
}