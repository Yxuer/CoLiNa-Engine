//
// Created by usuario on 19/8/19.
//

#include "Area.h"

Area::Area(std::map<std::string, Item*>* items, std::string n, std::string d, bool start)
: name(n), description(d), isStarting(start) {
    areaItems = items;
}

Area::~Area() {
    for (auto item : *areaItems) {
        delete item.second;
    }

    delete areaItems;
}

Item* Area::getItem(const std::string& itemName) {
    return (*areaItems)[itemName];
}