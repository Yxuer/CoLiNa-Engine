//
// Created by usuario on 19/8/19.
//

#include "Item.h"

Item::Item(std::map<std::string, std::map<std::string, std::vector<Action*>*>*>* actsPState, std::string n, std::string st)
: name(n), state(st){
    actionsPerState = actsPState;
}

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

const std::string& Item::getState() const {
    return state;
}

void Item::setState(const std::string &stateName) {
    state = stateName;
}