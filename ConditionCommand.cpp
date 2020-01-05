//
// Created by gal on 18/12/2019.
//

#include "ConditionCommand.h"
#include "Expression.h"
#include "ExpressionClass.h"
#include "BooleanIntrepter.h"
#include "SymbolTable.h"
#include "SetCommand.h"
/**
 * The method does what the command should and calculate the next index of the next  command in the vector 's'.
 *
 * @param s - The vector of the commands (from the Lexer.cpp)
 * @param i - The index of the start of the current command
 * @return The index of the next command in s (The index of the end of the current command + 1)
 */
int ConditionCommand::execute(vector<string> s, int i) {
    //ith place is the "if" word,i+1 left side of condition middle condition right is right expression
    Expression *leftExp=nullptr,*rightExp=nullptr;
    unordered_map<string, Var> nameToVar = SymbolTable::instance()->getNameToVar();
    Interpreter *interpLeft = new Interpreter(), *interpRight = new Interpreter();
    string setVariablesStr = "";

    // Iterate over an unordered_map using range based for loop
    for (std::pair<string, Var> element : nameToVar) {

            ostringstream valAsStr;
            valAsStr << element.second.getValue();
            string finalStrValue = valAsStr.str();
            setVariablesStr += element.first;
            setVariablesStr += "=";

            istringstream os(finalStrValue);
            double d;
            os>>d;
            finalStrValue = std::to_string(d);

            setVariablesStr += finalStrValue;
            setVariablesStr += ";";
    }

    interpLeft->setVariables(setVariablesStr);
    interpRight->setVariables(setVariablesStr);
    rightExp = interpRight->interpret(s[i + 3]);
    leftExp=interpLeft->interpret(s[i + 1]);

    BooleanIntrepter boolintre;
    string op=s[i+2];
    map<string, Command *> commands=SymbolTable::instance()->getCommands();
    Command *c;
    int j=i+6;
    //start from index i+4
    //this is the if command implemantion
   // cout<<"k";
    if(boolintre.intereptCondition(leftExp,op,rightExp)==1&& s[j]!="}"){
        while(s[j]!="}"){
            if(commands.find(s[j])==commands.end()){
                c= new SetCommand();//we dont have setcommand in our command map
            }
            else{
                c= commands[s[j]];
            }
            if(c!= nullptr){
                j = c->execute(s,j);
            }
        }
    }
    while (s[j].compare("}") != 0) {
        j++;
    }
//free
    free(leftExp);
    free(rightExp);
    free(interpLeft);
    free(interpRight);

    return j+2;
}