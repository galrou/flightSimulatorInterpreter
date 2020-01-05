//
// Created by idanbazel on 20/12/2019.
//

#ifndef FLIGHTSIMULATOR_SLEEPCOMMAND_H
#define FLIGHTSIMULATOR_SLEEPCOMMAND_H


#include "Command.h"

class SleepCommand: public Command{
public:
    virtual int execute(vector<string>s,int i);

};


#endif //FLIGHTSIMULATOR_SLEEPCOMMAND_H