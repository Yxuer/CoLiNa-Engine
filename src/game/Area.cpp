//
// Created by usuario on 19/8/19.
//

#include "Area.h"

Area::Area() {}

Area::~Area() {}

Item* Area::getItem(const std::string& itemName) {
    return areaItems[itemName];
}