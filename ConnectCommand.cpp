//
// Created by gal on 12/12/2019.
//

#include <thread>

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include "ConnectCommand.h"
#include "SymbolTable.h"
#include "ExpressionClass.h"
/**
*executes connectCommand and activates 2threads one is waiting for first input and the second one
*sends commands ro the simulator
**/
int ConnectCommand::execute(vector<string> s, int i) {


    Interpreter *interp = new Interpreter(); // The object of the Interpreter class

    Expression *exp = nullptr; // The object of the Expression class

    //evaluate the port-REMEMBER
    string ip=s[i+1];

    string prt="";
    for (unsigned int k = 1; k < (s[i+2]).length(); k++) {
        prt += s[i+2][k];
    }

    exp = interp->interpret(prt); // The mathematical expression is in s[i + 2]
    double ans = exp->calculate(); // Calculate the value of the mathematical expression
    int port = (int) ans;
    ConnectCommand*cm=new ConnectCommand;
    thread waitForConnThread(waitForConnection,port,cm);
    waitForConnThread.join();
    thread thread2(connectAsClient,port,cm);
    thread2.detach();

    return i + 4;

}
/**
* sets the socket
**/
void ConnectCommand::setSock(int sockk) {
    sock = sockk;
}
/**
* returns the socket
**/
int ConnectCommand::getSock() {
    return sock;
}

/**
* once the simulator connects this thread dies-it waits for connection
**/
void ConnectCommand::waitForConnection(int port, ConnectCommand *cm){
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
    }
    cm->setSock(client_socket);

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr("127.0.0.1");  //the localhost address
    address.sin_port = htons(port);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    //cm->setSock(is_connect);
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
    } else {
        // std::cout<<"Client is now connected to server" <<std::endl;
    }
}
/*
 * this function connects as client in thread once the value of a varible that has the diretion -> changes we will want to chnage
 * the value in the simulator as well
 * */
void ConnectCommand::connectAsClient(int port,ConnectCommand*cm) {
    int client_socket=cm->getSock();
    bool isDone=SymbolTable::instance()->getIsDone();
    if (port) {
        client_socket=cm->getSock();
    }
    // cout<<"inside client connect-out of while"<<endl;
    while(!isDone){
        bool is_msg_send = false;
//        cout<<"llll"<<endl;
        string instruction;
        // cout<<"kkk"<<endl;
        SymbolTable::instance()->_mutex.lock();
        //instruction.insert(0, SymbolTable::instance()->getInstruction());
        instruction=SymbolTable::instance()->getInstruction();
        // SymbolTable::instance()->clearInstruction();
        bool leftToSend=SymbolTable::instance()->getLeftToSend();
        while(leftToSend){
            //char buff[instruction.size()+1];
//            copy(instruction.begin(),instruction.end(),buff);
//            buff[instruction.size()]='\0';
            int is_sent = send(client_socket ,instruction.c_str() , instruction.length() , 0 );
            //cout << instruction << endl;
            if (is_sent == -1) {
                std::cout<<"Error sending message"<<std::endl;
            }
            is_msg_send = true;
            SymbolTable::instance()->_mutex.unlock();
            SymbolTable::instance()->setLeftToSend(false);
            //instruction.clear();
            leftToSend=SymbolTable::instance()->getLeftToSend();

        }

        isDone=SymbolTable::instance()->getIsDone();
        if (!is_msg_send) {
            SymbolTable::instance()->_mutex.unlock();
        }
    }
//    char buffer[1024] = {0};
//    bool flag=false;

    close(client_socket);
}

//  int valread = read( client_socket , buffer, 1024);
//std::cout<<buffer<<std::endl;
