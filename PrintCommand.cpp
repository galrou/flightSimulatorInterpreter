//
// Created by idanbazel on 20/12/2019.
//

#include <unordered_map>
#include "PrintCommand.h"
#include "ExpressionClass.h"
#include "Var.h"
#include "SymbolTable.h"

using namespace std;

/**
 * The method does what the command should and calculate the next index of the next  command in the vector 's'.
 *
 * @param s - The vector of the commands (from the Lexer.cpp)
 * @param i - The index of the start of the current command
 * @return The index of the next command in s (The index of the end of the current command + 1)
 */
int PrintCommand::execute(vector<string>s, int i) {
    //cout<<"in print defintion"<<endl;
    //check if the thing we want to print contains " -if it contains its not an expression
    //if it doesnt it some var we want to evaluate
    if (s[i+1].find("\"") != std::string::npos) {

        string messageWithoutQuoMarks = "";

        for (unsigned int j = 1; j < s[i + 1].length() - 1; j++) {
            messageWithoutQuoMarks += s[i + 1][j];
        }

        //found-print it
        cout<<messageWithoutQuoMarks<<endl;
        return i+3;
    }
    //else its some var or value we want to evaluate
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

    cout<<ans<<endl;
    return i+3;
}