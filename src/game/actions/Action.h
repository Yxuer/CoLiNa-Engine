//
// Created by luis on 16/8/19.
//

#ifndef UNTITLED_ACTION_H
#define UNTITLED_ACTION_H

#include <vector>
#include <string>
#include <map>

class GameManager;

class Action {

protected:
    std::vector<std::string> listOfParameterNames;
    std::map<std::string, std::string> parameters;
    GameManager *gameManager;

public:
    Action(GameManager *manager);
    virtual ~Action();

    virtual void run();
    const std::vector<std::string>& getListOfParameterNames();
    void setParameter(const std::string& parameter, const std::string& value);
};

#endif //UNTITLED_ACTION_H
