//
// Created by idanbazel on 12/12/2019.
//

#ifndef FLIGHTSIMULATOR_OPENSERVERCOMMAND_H
#define FLIGHTSIMULATOR_OPENSERVERCOMMAND_H


#include "Command.h"
using namespace std;
class OpenServerCommand: public Command{
private:
    int clientSocket;
public:
    OpenServerCommand(){};
    void setClientSocket(int);
    int getClientSocket();
    static void waitForConnection(int,OpenServerCommand*);
    virtual int execute(vector<string>,int);
    static void runServer(int,OpenServerCommand*);
    vector<string> getValuesVector(char*);
    vector<string> getPathsVector();
    void updatePaths(vector<string>, vector<string>);
    string getLastChunk(string);

};


#endif //FLIGHTSIMULATOR_OPENSERVERCOMMAND_H