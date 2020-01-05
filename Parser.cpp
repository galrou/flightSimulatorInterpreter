//
// Created by gal on 12/12/2019.
//

#include "Parser.h"
#include "Command.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "SymbolTable.h"
#include "SetCommand.h"
#include <iostream>
#include <iterator>
#include <map>

using namespace std;
/**
 * parses the commands and executes them its get a vector from the lexer
 */
void Parser::parse(vector<string> text) {
    int index=0,size;
    size=text.size();
    map<string, Command *> commands=SymbolTable::instance()->getCommands();
    unordered_map<string, Var> nameToVar;
    Command *c;
    while(index<size) {
        nameToVar=SymbolTable::instance()->getNameToVar();
        /**
         * Check if the command exists in the command map-if it isent then is its setCommand.
         * (if it will cause problems we mighht want to add a condition checking if its in the var maps).
         */
        if(commands.find(text[index])==commands.end()&&nameToVar.find(text[index])!=nameToVar.end()){
            c= new SetCommand();//we dont have setcommand in our command map
        }
        else{
            c= commands[text[index]];
        }
        if(c!= nullptr){
            index = c->execute(text,index);
        }
    }
    SymbolTable::instance()->setIsDone(true);
    SymbolTable::instance()->setServerDone(true);


}