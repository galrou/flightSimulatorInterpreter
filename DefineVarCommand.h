//
// Created by gal on 12/12/2019.
//

#ifndef FLIGHTSIMULATOR_DEFINEVARCOMMAND_H
#define FLIGHTSIMULATOR_DEFINEVARCOMMAND_H


#include "Command.h"
using namespace std;
class DefineVarCommand: public Command {
public:
    virtual int execute(vector<string>s,int i);

};


#endif //FLIGHTSIMULATOR_DEFINEVARCOMMAND_H