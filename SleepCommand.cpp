//
// Created by idanbazel on 20/12/2019.
//

#include <thread>
#include "SleepCommand.h"
#include "ExpressionClass.h"
#include "Expression.h"
#include "Var.h"
#include "SymbolTable.h"
#include <chrono>
#include <unordered_map>

using namespace std;

/**
 * The method does what the command should and calculate the next index of the next  command in the vector 's'.
 *
 * @param s - The vector of the commands (from the Lexer.cpp)
 * @param i - The index of the start of the current command
 * @return The index of the next command in s (The index of the end of the current command + 1)
 */
int SleepCommand::execute(vector<string> s, int i) {
    Interpreter* interp = new Interpreter();
    unordered_map<string, Var> nameToVar = SymbolTable::instance()->getNameToVar();
    Expression* exp = nullptr;

    string setVariablesStr = "";

    // Iterate over an unordered_map using range based for loop
    for (std::pair<string, Var> element : nameToVar)
    {
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

    interp->setVariables(setVariablesStr);
    exp = interp->interpret(s[i + 1]);
    double ans = exp->calculate();
    std::this_thread::sleep_for(std::chrono::milliseconds(int(ans)));
    return i+3;
}