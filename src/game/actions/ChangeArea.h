//
// Created by usuario on 29/08/19.
//

#ifndef COLINA_ENGINE_CHANGEAREA_H
#define COLINA_ENGINE_CHANGEAREA_H

#include "Action.h"

class ChangeArea : public Action {
    public:
        ChangeArea();
        virtual void run() override ;
};


#endif //COLINA_ENGINE_CHANGEAREA_H
