//
// Created by luis on 16/8/19.
//

#ifndef UNTITLED_AREA_H
#define UNTITLED_AREA_H

#include "Item.h"

#include <map>

class Area {
private:
    std::string name;
    std::map<std::string, Item*>* areaItems;
    std::string description;
    bool isStarting;

public:
    Area(std::map<std::string, Item*>* items, std::string n, std::string d, bool start);
    virtual ~Area();

    void examine();

    Item* getItem(const std::string& itemName);
};

#endif //UNTITLED_AREA_H
