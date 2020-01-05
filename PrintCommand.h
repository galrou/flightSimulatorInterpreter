//
// Created by idanbazel on 20/12/2019.
//

#ifndef FLIGHTSIMULATOR_PRINTCOMMAND_H
#define FLIGHTSIMULATOR_PRINTCOMMAND_H


#include "Command.h"

class PrintCommand: public Command {
public:
    virtual int execute(vector<string>,int i);


};


#endif //FLIGHTSIMULATOR_PRINTCOMMAND_H