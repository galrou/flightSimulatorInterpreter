//
// Created by gal on 12/12/2019.
//
#include "SymbolTable.h"
#include "DefineVarCommand.h"
#include "ExpressionClass.h"

/**
 * The method does what the command should and calculate the next index of the next  command in the vector 's'.
 *
 * @param s - The vector of the commands (from the Lexer.cpp)
 * @param i - The index of the start of the current command
 * @return The index of the next command in s (The index of the end of the current command + 1)
 */
int DefineVarCommand::execute(vector<string> s, int i) {
    //creates a var objects
    Var var = Var();
    var.setName(s[i + 1]);
    if (s[i + 2] == "->" || s[i + 2] == "<-") {
        var.setDirection(s[i + 2]);
        var.setSim(s[i + 4]);
        var.setName(s[i+1]); //-----
        //insert to simToVar map
        SymbolTable::instance()->insertToSimToVar(s[i + 4], var);
        // Updating the  value of the variable s[i] in the NameToVar map
        SymbolTable::instance()->insertToNameToVar(s[i + 1], var); //-----
    } else if (s[i + 2] == "=") {
        //=============================
        unordered_map<string, Var> nameToVar = SymbolTable::instance()->getNameToVar();

        Interpreter *interp = new Interpreter(); // The object of the Interpreter class

        Expression *exp = nullptr; // The object of the Expression class

        string setVariablesStr = ""; // A string of the setVariables Method in the Interpreter class

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

        // Calculate the value of the current variable (s[i]) by its mathematical expression
        interp->setVariables(setVariablesStr); // Set  the other variables values
        exp = interp->interpret(s[i + 3]); // The mathematical expression is in s[i + 2]
        double ans = exp->calculate(); // Calculate the value of the mathematical expression

        Var ansVar = nameToVar[s[i + 1]]; // Var instance in order to update the value of the current variable (s[i])

        ansVar.setValue(ans);

        // Updating the value of the variable s[i] in the NameToVar map
        SymbolTable::instance()->insertToNameToVar(s[i + 1], ansVar);

        // If s[i + 1] has had one of the arrows (-> OR <-) we will update its value in SimToVar map also
        if (ansVar.getHasDirection() == true) {
            if(ansVar.getDirection()==1)
            {
                string instruction="";
                //concat the sim
                instruction+=ansVar.getSim();
                //remove the "/
                instruction.erase(0,2);
                //insert "set
                string beg;
                beg+='"';
                beg+="set ";
                instruction.insert(0,beg);
                ostringstream valAsStr;
                valAsStr <<ansVar.getValue();
                string finalStrValue = valAsStr.str();
                instruction+=finalStrValue;
                instruction+=" ";
                //concat the value
                instruction+="\r\n";
                //insert into our instructions queue
                //cout<<instruction<<endl;
                SymbolTable::instance()->insertToInstructions(instruction);
            }
            //dont need to update it if its "->" the server will
            SymbolTable::instance()->insertToSimToVar(ansVar.getSim(), ansVar);
        }
    }


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