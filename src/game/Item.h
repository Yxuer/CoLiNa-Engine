//
// Created by luis on 16/8/19.
//

#ifndef UNTITLED_ITEM_H
#define UNTITLED_ITEM_H

#include "actions/Action.h"

#include <map>

class Item {
private:
    std::string name;
    std::map<std::string, std::map<std::string, Action>> actionsPerState;
    std::string state;

public:
    Item();
    virtual ~Item();

    void act(const std::string& action);
};

#endif //UNTITLED_ITEM_H
