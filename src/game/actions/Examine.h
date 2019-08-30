//
// Created by usuario on 30/08/19.
//

#ifndef COLINA_ENGINE_EXAMINE_H
#define COLINA_ENGINE_EXAMINE_H

#include "Action.h"

class Examine : public Action {
    public:
        Examine();
        virtual void run() override ;
};


#endif //COLINA_ENGINE_EXAMINE_H
