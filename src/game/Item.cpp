//
// Created by usuario on 19/8/19.
//

#include "Item.h"

Item::Item(std::map<std::string, std::map<std::string, Action**>>* actsPState, std::string n, std::string st)
: name(n), state(st){
    actionsPerState = actsPState;
}

Item::~Item() {}

const std::string& Item::getState() const {
    return state;
}

void Item::setState(const std::string &stateName) {
    state = stateName;
}