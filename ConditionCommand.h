//
// Created by gal on 18/12/2019.
//

#ifndef FLIGHTSIMULATOR_CONDITIONCOMMAND_H
#define FLIGHTSIMULATOR_CONDITIONCOMMAND_H


#include "Command.h"

class ConditionCommand:public Command {
    //in case of commands finding th next EOL isnt enough
    virtual int execute(vector<string>, int);
};

#endif //FLIGHTSIMULATOR_CONDITIONCOMMAND_H