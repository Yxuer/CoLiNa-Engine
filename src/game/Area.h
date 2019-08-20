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
    std::map<std::string, Item*> areaItems;
    std::string description;

public:
    Area();
    virtual ~Area();

    void examine();

    Item* getItem(const std::string& itemName);
};

#endif //UNTITLED_AREA_H
