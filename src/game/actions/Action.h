//
// Created by luis on 16/8/19.
//

#ifndef UNTITLED_ACTION_H
#define UNTITLED_ACTION_H

#include <vector>
#include <string>
#include <map>
#include <set>

class GameManager;

class Action {

protected:

    // List of parameter names for the specific action
    std::vector<std::string> listOfParameterNames;

    // List of parameter values (as strings)
    std::map<std::string, std::string> parameters;

public:

    // Reference to the GameManager object
    static GameManager *gameManager;

    // List of all possible actions
    static std::set<std::string> listOfActions;

    Action();
    virtual ~Action();

    virtual void run() = 0;
    static Action* make_action(const std::string& actionName);     /// Action factory

    const std::vector<std::string>& getListOfParameterNames();
    void setParameter(const std::string& parameter, const std::string& value);
};

#endif //UNTITLED_ACTION_H
