//
// Created by luis on 16/8/19.
//

#ifndef UNTITLED_ITEM_H
#define UNTITLED_ITEM_H

#include "actions/Action.h"

#include <map>
#include <vector>

class Item {
private:
    std::string name;
    std::map<std::string, std::map<std::string, std::vector<Action*>*>*>* actionsPerState;
    std::string state;

public:
    Item(std::map<std::string, std::map<std::string, std::vector<Action*>*>*>* actsPState, std::string n, std::string st);
    virtual ~Item();

    void act(const std::string& action);

    const std::string& getState() const;
    void setState(const std::string& stateName);
};

#endif //UNTITLED_ITEM_H
