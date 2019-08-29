//
// Created by usuario on 19/8/19.
//

#include "Item.h"
#include "util/GameExceptions.h"

/*Item constructor.*/
Item::Item(std::map<std::string, std::map<std::string, std::vector<Action*>*>*>* actsPState, std::string n, std::string st)
: name(n), state(st){
    actionsPerState = actsPState;
}

/*Item destructor. Destroys all its associated actions */
Item::~Item() {
    for (auto state : *actionsPerState) {
        for (auto command : *(state.second)) {
            for (auto action : *(command.second)) {
                delete action;
            }
            delete command.second;
        }
        delete state.second;
    }
    delete actionsPerState;
}

/*Returns the current state of the item*/
const std::string& Item::getState() const {
    return state;
}

/*Sets the state of the item to the given value*/
void Item::setState(const std::string &stateName) {
    state = stateName;

    if (actionsPerState->find(stateName) == actionsPerState->end()) {
        throw UnknownStateError();
    }
}

/*Runs a given command on this item. It also checks if the item is in an invalid state,
 * or if the action does not exist in this state*/
void Item::act(const std::string &action) {
    auto stateCommands = actionsPerState->find(state);
    if (stateCommands == actionsPerState->end()) {
        throw UnknownStateError();
    }

    auto actionList = stateCommands->second->find(action);
    if (actionList == stateCommands->second->end()) {
        throw UnknownActionException();
    }

    for (auto runAction : *actionList->second) {
        runAction->run();
    }
}