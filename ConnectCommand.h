//
// Created by gal on 12/12/2019.
//

#ifndef FLIGHTSIMULATOR_CONNECTCOMMAND_H
#define FLIGHTSIMULATOR_CONNECTCOMMAND_H


#include "Command.h"
using namespace std;
class ConnectCommand: public Command {
private:
    int sock;
public:
    void setSock(int sockk);
    int getSock();
    static void waitForConnection(int port,ConnectCommand*cm);
    virtual int execute(vector<string>s,int i);
    static void connectAsClient(int port,ConnectCommand*cm);

};


#endif //FLIGHTSIMULATOR_CONNECTCOMMAND_H
