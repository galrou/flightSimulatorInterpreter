//
// Created by idanbazel on 12/12/2019.
//
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <cstring>


#include "OpenServerCommand.h"
#include "SymbolTable.h"
#include "ExpressionClass.h"

using namespace std;

/**
 * The method does what the command should and calculate the next index of the next  command in the vector 's'.
 *
 * @param s - The vector of the commands (from the Lexer.cpp)
 * @param i - The index of the start of the current command
 * @return The index of the next command in s (The index of the end of the current command + 1)
 */
int OpenServerCommand::execute(vector<string> s, int i) {

    unordered_map<string, Var> nameToVar = SymbolTable::instance()->getNameToVar();
    Interpreter *interp = new Interpreter(); // The object of the Interpreter class
    Expression *exp = nullptr; // The object of the Expression class

    // Calculate the value of the current port (s[i + 1]) by its mathematical expression
    exp = interp->interpret(s[i + 1]); // The mathematical expression is in s[i + i]
    double ans = exp->calculate(); // Calculate the value of the mathematical expression

    //evaluate the value of port before
    //port
    int port = ans;
    //create an instance of this class
    OpenServerCommand*opc=new OpenServerCommand();
    thread waitForFirstInput(waitForConnection,port,opc);
    //activate the thread that waits for connection itll die once getting one
    waitForFirstInput.join();
    thread thread1(runServer, port,opc);
    thread1.detach();

    //  Return the index of the next line. If we done with all the lines, we will return -1.
    int nextLineIndex = s.size(); // The index of the next line that we will return
    for (unsigned int index = i; index < s.size(); index++) {

        //  If we saw the End Of Line symbol (;EOL;).
        if (s[index].compare(";EOL;") == 0) {
            nextLineIndex = index + 1;
            break;
        }
    }
    return nextLineIndex;
}



/**
 * The method updates the current socket to be 'clientSocket1'.
 * @param clientSocket1 - The socket
 */
void OpenServerCommand::setClientSocket(int clientSocket1) {
    clientSocket=clientSocket1;

}

/**
 *
 * @return The current clientSocket
 */
int OpenServerCommand::getClientSocket() {
    return clientSocket;

}

/**
 * The method waits for the first input.
 *
 * @param port - The port number
 * @param opc - The opject
 */
void OpenServerCommand::waitForConnection(int port, OpenServerCommand *opc) {
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        exit(0);
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        exit(0);
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr<<"Error during listening command"<<std::endl;
        exit(0);
    }

    int addrLen = sizeof(address);
    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *)&address,
                               (socklen_t*)&addrLen);
    opc->setClientSocket(client_socket);

    if (client_socket == -1) {
        std::cerr<<"Error accepting client"<<std::endl;
        exit(0);
    }
}

/**
 * The method runs the server.
 *
 * @param port - The port number
 * @param opc - The object
 */
void OpenServerCommand::runServer(int port,OpenServerCommand*opc) {

    int client_socket = opc->getClientSocket();

    //reading from client
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);

    vector<string> pathsVector = (*opc).getPathsVector(); // The paths vector
    vector<string> valuesVector;
    string cuttedInformation = "";

    if (valread || port) {
        cuttedInformation = "";
    }

    while (buffer[0] != '\n')  {
        //std::cout<<buffer<<std::endl;


        string currentChunk = (*opc).getLastChunk(buffer); // The cutted chunck (If exists)
        // If we have not a chunk
        if (currentChunk == "") {
            cuttedInformation += buffer;
            char* cuttedInformationCpy = (char*) malloc(cuttedInformation.length() * sizeof(char) + 1);

            // If malloc failed
            if (!cuttedInformationCpy) {
                cout<<"Malloc failed -> openServerCommand.cpp"<<endl;
                exit(0);
            }
            // Copy to type char*
            for (unsigned int i = 0; i <  cuttedInformation.length(); i++) {
                cuttedInformationCpy[i] = cuttedInformation[i];
            }
            valuesVector = (*opc).getValuesVector(cuttedInformationCpy); // The vector of the splitted values
            cuttedInformation = "";
            free(cuttedInformationCpy);
        }

            // If we have a chunk
        else {
            string bufferWithoutLastChunck = "";
            size_t start = 0;
            string bufferCpy = "";

            for (unsigned int k = 0; buffer[k] != '\0'; k++) {
                bufferCpy += buffer[k];
            }

            // If at the previous iteration we did not have a last chunk without '\n'
            if (cuttedInformation == "") {

                // Get buffer without the last chunck
                while ((start = bufferCpy.find("\n")) != std::string::npos) {
                    bufferWithoutLastChunck += bufferCpy.substr(0, start);
                    bufferCpy.erase(0, start + 1);
                }
                char* bufferWithoutLastChunckCpy = (char*) malloc(bufferWithoutLastChunck.length() * sizeof(char)  + 1);

                // If malloc failed
                if (!bufferWithoutLastChunckCpy) {
                    cout<<"Malloc failed -> openServerCommand.cpp"<<endl;
                    exit(0);
                }

                // Copy to type char*
                for (unsigned int i = 0; i <  bufferWithoutLastChunck.length(); i++) {
                    bufferWithoutLastChunckCpy[i] = bufferWithoutLastChunck[i];
                }
                valuesVector = (*opc).getValuesVector(bufferWithoutLastChunckCpy); // The vector of the splitted values
                cuttedInformation = currentChunk;
                free(bufferWithoutLastChunckCpy);
            }

                // If at the previous iteration we had a chunk without '\n'
            else {

                // Get buffer without the last chunck
                while ((start = bufferCpy.find("\n")) != std::string::npos) {
                    bufferWithoutLastChunck += bufferCpy.substr(0, start);
                    bufferCpy.erase(0, start + 1);
                }
                cuttedInformation += bufferWithoutLastChunck;
                char* bufferWithoutLastChunckCpy = (char*) malloc(cuttedInformation.length() * sizeof(char)  + 1);

                // If malloc failed
                if (!bufferWithoutLastChunckCpy) {
                    cout<<"Malloc failed -> openServerCommand.cpp"<<endl;
                    exit(0);
                }

                // Copy to type char*
                for (unsigned int i = 0; i <  cuttedInformation.length(); i++) {
                    bufferWithoutLastChunckCpy[i] = cuttedInformation[i];
                }

                valuesVector = (*opc).getValuesVector(bufferWithoutLastChunckCpy); // The vector of the splitted values
                cuttedInformation = bufferCpy;
            }
        }
        (*opc).updatePaths(pathsVector, valuesVector);

        valread = read(client_socket , buffer, 1024);
    }

    // Check if we finished and then we will close the socket.
    if(SymbolTable::instance()->getServerDone()){
        close(opc->getClientSocket());
    }
}


/**
 * The function checks if the string 'str' has a cutted chunck without '\n'.
 * If yes - Return thecutted chunck. If not - Return the empty string.
 * @param str - The string that we check
 * @return - As described above (Thw cutted chunck or the empty string)
 */
string OpenServerCommand::getLastChunk(string str) {

    string copyStr = ""; // The answer

    if (copyStr[copyStr.length() - 1] == '\n') {
        return copyStr;
    }

    size_t start = 0;

    // Copying the string 'str' into 'copyStr'
    for (unsigned int i = 0; i < str.length(); i++) {
        copyStr += str[i];
    }

    // Remove every thing but the last chunck
    while ((start = copyStr.find("\n")) != std::string::npos) {
        copyStr.erase(0, start + 1);
    }

    return copyStr;
}

/**
 * The method returns a vector of the splitted values of the string 'str'.
 *
 * @param str - The string that we want to split (str = "num1,num2,num3,num4, , , , ,)
 * @return ansVec - The vector with the splitted values (ansVec = (num1, num2, num3, num4, , , ,)
 */
vector<string> OpenServerCommand::getValuesVector(char * str) {

    string copyStr = "";
    vector<string> ansVec;
    size_t start = 0;

    //  Copying to string type
    for (unsigned int i = 0; str[i] != '\0'; i++) {
        copyStr += str[i];
    }

    // Split by ',' and push back into the ansVec
    while ((start = copyStr.find(",")) != std::string::npos) {

        // Get the current subString
        string currentStr = copyStr.substr(0, start);

        // Push back the current subString into the ansVec
        ansVec.push_back(currentStr);

        // Remove the current subString out of the string
        copyStr.erase(0, start + 1);
    }
    ansVec.push_back(copyStr);

    string newAnsVecT = "";
    for (unsigned int t = 0; t < ansVec.size(); t++) {

        for (unsigned int j = 0; j < ansVec[t].length(); j++) {
            if (ansVec[t][j] != ' ' && ansVec[t][j] != '\n') {
                newAnsVecT += ansVec[t][j];
            }
        }

        istringstream os(newAnsVecT);
        double d;
        os >> d;
        string answerVecElem = std::to_string(d);
        ansVec[t] = answerVecElem;
        newAnsVecT = "";
    }

    return ansVec;
}

/**
 * @return A vector with 36 paths
 */
vector<string> OpenServerCommand::getPathsVector() {

    vector<string> pathsVec; // The vector of the paths

    pathsVec.push_back("\"/instrumentation/airspeed-indicator/indicated-speed-kt\"");           // 1
    pathsVec.push_back("\"/sim/time/warp\"");                                                   // 2
    pathsVec.push_back("\"/controls/switches/magnetos\"");                                      // 3
    pathsVec.push_back("\"/instrumentation/heading-indicator/offset-deg\"");                    // 4
    pathsVec.push_back("\"/instrumentation/altimeter/indicated-altitude-ft\"");                 // 5
    pathsVec.push_back("\"/instrumentation/altimeter/pressure-alt-ft\"");                       // 6
    pathsVec.push_back("\"/instrumentation/attitude-indicator/indicated-pitch-deg\"");          // 7
    pathsVec.push_back("\"/instrumentation/attitude-indicator/indicated-roll-deg\"");           // 8
    pathsVec.push_back("\"/instrumentation/attitude-indicator/internal-pitch-deg\"");           // 9
    pathsVec.push_back("\"/instrumentation/attitude-indicator/internal-roll-deg\"");            // 10
    pathsVec.push_back("\"/instrumentation/encoder/indicated-altitude-ft\"");                   // 11
    pathsVec.push_back("\"/instrumentation/encoder/pressure-alt-ft\"");                         // 12
    pathsVec.push_back("\"/instrumentation/gps/indicated-altitude-ft\"");                       // 13
    pathsVec.push_back("\"/instrumentation/gps/indicated-ground-speed-kt\"");                   // 14
    pathsVec.push_back("\"/instrumentation/gps/indicated-vertical-speed\"");                    // 15
    pathsVec.push_back("\"/instrumentation/heading-indicator/indicated-heading-deg\"");         // 16
    pathsVec.push_back("\"/instrumentation/magnetic-compass/indicated-heading-deg\"");          // 17
    pathsVec.push_back("\"/instrumentation/slip-skid-ball/indicated-slip-skid\"");              // 18
    pathsVec.push_back("\"/instrumentation/turn-indicator/indicated-turn-rate\"");              // 19
    pathsVec.push_back("\"/instrumentation/vertical-speed-indicator/indicated-speed-fpm\"");    // 20
    pathsVec.push_back("\"/controls/flight/aileron\"");                                         // 21
    pathsVec.push_back("\"/controls/flight/elevator\"");                                        // 22
    pathsVec.push_back("\"/controls/flight/rudder\"");                                          // 23
    pathsVec.push_back("\"/controls/flight/flaps\"");                                           // 24
    pathsVec.push_back("\"/controls/engines/engine/throttle\"");                                // 25
    pathsVec.push_back("\"/controls/engines/current-engine/throttle\"");                        // 26
    pathsVec.push_back("\"/controls/switches/master-avionics\"");                               // 27
    pathsVec.push_back("\"/controls/switches/starter\"");                                       // 28
    pathsVec.push_back("\"/engines/active-engine/auto-start\"");                                // 29
    pathsVec.push_back("\"/controls/flight/speedbrake\"");                                      // 30
    pathsVec.push_back("\"/sim/model/c172p/brake-parking\"");                                   // 31
    pathsVec.push_back("\"/controls/engines/engine/primer\"");                                  // 32
    pathsVec.push_back("\"/controls/engines/current-engine/mixture\"");                         // 33
    pathsVec.push_back("\"/controls/switches/master-bat\"");                                    // 34
    pathsVec.push_back("\"/controls/switches/master-alt\"");                                    // 35
    pathsVec.push_back("\"/engines/engine/rpm\"");                                              // 36

    // Return the vector of the paths
    return pathsVec;
}

/**
 * The method updates the values that we got from the simulator (in 'values' vector) by the suitable
 * path (in 'paths' vector). We will update that in "SymbolTable" class in SimToVar and NameToVar maps.
 * If the path is not exist in the 'SimToVar' map' we will ignore the current path.
 *
 * @param paths - A vector of all the paths (from the XML file)
 * @param values - A vector of all the values (from the simulator)
 */
void OpenServerCommand::updatePaths(vector<string> paths, vector<string> values) {


    unordered_map<string, Var> simToVarMap = SymbolTable::instance()->getSimToVar(); // The 'simToVar' map

    for (unsigned int i = 0; i < values.size(); i++) {

        int index = i % paths.size();

        string currentPath = paths[index]; // The current path in the 'paths' vector

        // If the current path exists in 'simToVar' map
        if ((simToVarMap.find(currentPath) != simToVarMap.end()) && values[index] != "") {

            Var newVar = simToVarMap[currentPath]; // The new updated Var of the current path
            double newValue = stod(values[index]); // The new value of the variable of the current path
            // Updating the current value
            newVar.setValue(newValue);

            // Insert the 'newVar' of the 'currentPath' to 'simToVar' map
            SymbolTable::instance()->insertToSimToVar(currentPath, newVar);

            string variableName = newVar.getName(); // The name of the original variable of the 'currentPath'

            // Insert the 'newVar' (with the 'newValue') into the 'nameToVar' map.
            SymbolTable::instance()->insertToNameToVar(variableName, newVar);
        }
    }
}