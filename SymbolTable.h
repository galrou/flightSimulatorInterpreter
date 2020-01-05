//
// Created by gal on 12/12/2019.
//

#ifndef FLIGHTSIMULATOR_SYMBOLTABLE_H
#define FLIGHTSIMULATOR_SYMBOLTABLE_H

#include <string>
#include <iostream>
#include <map>
#include <unordered_map>
#include <memory>
#include "Command.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "OpenServerCommand.h"
#include "Var.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "ConditionCommand.h"
#include "WhileCommand.h"
#include <queue>
#include <mutex>
#include <thread>

using namespace std;
//using singleton pattren to make it visible to all classes
/**
 * this a singleton class here we store all of our maps we used singletn so all
 * the classes will have acsses to those members
 */
class SymbolTable {
private:
    //maps x for instance to a var object that holds all the information
    unordered_map <string,Var>nameTovar;
    //this map helps handles expressions
    unordered_map<string,double>varToValue;
    //so we can update the var from the server
    unordered_map<string,Var>simToVar;
    //maps string to command object shared ptr is a smart pointer so we dont have to deal with memory managnent-it frees it self
    map<string,Command*> commands;
    //the instructions that the simulator will get from the client
    queue<string> instructions;
    string instruction ="";
    volatile  bool isDone=false;
    volatile  bool leftToSend;
    volatile  bool serverDone=false;
    static SymbolTable *symbol_instance;
public:
    mutex _mutex;
public:
    /**
     * constructor
     */
    SymbolTable(){
        _mutex.lock();
        commands.insert(std::make_pair(std::string("openDataServer"),new OpenServerCommand()));
        commands.insert(std::make_pair("connectControlClient",new ConnectCommand()));
        commands.insert(std::make_pair("var",new DefineVarCommand()));
        commands.insert(std::make_pair("Sleep",new SleepCommand()));
        commands.insert(std::make_pair("Print",new PrintCommand()));
        commands.insert(std::make_pair("if",new ConditionCommand()));
        commands.insert(std::make_pair("while",new WhileCommand()));
        leftToSend=false;
        instruction="";
        _mutex.unlock();
    };
    /**
     * a flag that checks if the reading from file is finished if so we will close the socket at the server side
     * @param f
     */
    void setServerDone(bool f){
        _mutex.lock();
        serverDone=f;
        _mutex.unlock();
    }
    bool getServerDone(){
        return serverDone;
    }

    //we use it it whenever we see Var x -> or <- or = to something
    /**
     *  insert an item to a map that maps a name to  var object
     * @param name1
     * @param var
     */
    void insertToNameToVar(string name1,Var var){
        _mutex.lock();
        nameTovar[name1]=var;
        _mutex.unlock();
    }
    /**
     * insert an item to a map that maps a sim to its var object
     * only variables that has -> or <- are here
     * @param sim
     * @param var
     */
    void insertToSimToVar(string sim,Var var){
        _mutex.lock();
        //simToVar.insert(std::pair<string, Var>(sim, var));
        simToVar[sim]=var;
        _mutex.unlock();
    }
 /**
 * a function that gets a flag and sets isDone flag to this flag the isDone is used i the connectClinet to
  * indectae whether the eading from file is  done or not
 * @param flag
 */
    void setIsDone(bool flag){
        _mutex.lock();
        isDone=flag;
        _mutex.unlock();
    }
    /**
     * return the isDone flag
     * @return
     */
    bool getIsDone(){
        return isDone;
    }
    /**
     * set leftToSend flag this flag is true if theres a message that hasnt been sent yet to the simulator
     * @param leftToSendd
     */
    void setLeftToSend(bool leftToSendd){
        _mutex.lock();
        leftToSend=leftToSendd;
        _mutex.unlock();
    }
    /**
     * get the leftToSend flag
     * @return
     */
    bool getLeftToSend(){
        return leftToSend;
    }

    /**
     * set the command we want to send
     * @param ins
     */
    void setInstruction(string ins){
        _mutex.lock();
        instruction=ins;
        leftToSend=true;
        _mutex.unlock();
    }
    /**
     * return the mesage we need to send
     * @return
     */
    string getInstruction() {
        return instruction;
    }
    /**
     * insert the message we want to send to the simulaor
     * @param instruction1
     */
    void insertToInstructions(string instruction1){
        _mutex.lock();
        instructions.push(instruction1);
        _mutex.unlock();
    }
    /**
     *  returns an instace of this class
     * @return
     */
    static SymbolTable* instance()
    {
        if (!symbol_instance)
            symbol_instance = new SymbolTable();
        return symbol_instance;
    }

/**
 * returns the command map
 * @return
 */
    map<string,Command*> getCommands(){
        return commands;
    }
    /**
     * return the nametovar map
     * @return
     */
    unordered_map<string,Var>getNameToVar(){
        return nameTovar;
    }
 /**
 * return the simtovar map
 * @return
 */
    unordered_map<string, Var> getSimToVar(){
        return simToVar;
    }
};


#endif //FLIGHTSIMULATOR_SYMBOLTABLE_H