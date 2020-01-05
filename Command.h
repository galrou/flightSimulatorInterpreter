//
// Command interface
//

#ifndef FLIGHTSIMULATOR_COMMAND_H
#define FLIGHTSIMULATOR_COMMAND_H

#include <string>
#include <vector>

using namespace std;
class Command {
public:
    virtual int execute(vector<string>s,int i)=0;
    virtual ~Command(){}
};



#endif //FLIGHTSIMULATOR_COMMAND_H
