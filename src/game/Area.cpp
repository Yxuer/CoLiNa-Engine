//
// Created by usuario on 19/8/19.
//

#include "Area.h"

#include <iostream>

/*Area constructor*/
Area::Area(std::map<std::string, Item*>* items, std::string n, std::string d, bool start)
: name(n), description(d), isStarting(start) {
    areaItems = items;
}

/*Area destructor. Deletes all its items*/
Area::~Area() {
    for (auto item : *areaItems) {
        delete item.second;
    }

    delete areaItems;
}

/*Returns an item on this area, given its name*/
Item* Area::getItem(const std::string& itemName) {
    if (areaItems->find(itemName) == areaItems->end()) {
        return nullptr;
    }
    return (*areaItems)[itemName];
}

/*Prints the description of the current area*/
void Area::examine() {
    std::cout << description;
}