//
// Created by usuario on 20/8/19.
//

#ifndef COLINA_ENGINE_SETSTATE_H
#define COLINA_ENGINE_SETSTATE_H

#include "Action.h"

#include <string>

class SetState : public Action {
    public:
        SetState(GameManager *mgr, std::string item, std::string state);
        virtual void run() override ;
};


#endif //COLINA_ENGINE_SETSTATE_H
