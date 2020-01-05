//
// Created by idanbazel on 20/12/2019.
//

#ifndef FLIGHTSIMULATOR_SETCOMMAND_H
#define FLIGHTSIMULATOR_SETCOMMAND_H


#include "Command.h"
#include "ExpressionClass.h"

class SetCommand: public Command {
public:
    SetCommand(){};
    virtual int execute(vector<string>s,int i);
};



#endif //FLIGHTSIMULATOR_SETCOMMAND_H