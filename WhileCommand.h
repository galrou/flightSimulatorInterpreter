//
// Created by gal on 18/12/2019.
//

#ifndef FLIGHTSIMULATOR_WHILECOMMAND_H
#define FLIGHTSIMULATOR_WHILECOMMAND_H


#include "Command.h"

class WhileCommand: public Command{
    virtual int execute(vector<string>s,int i);

};


#endif //FLIGHTSIMULATOR_WHILECOMMAND_H