//
// Created by idanbazel on 20/12/2019.
//

#include "SetCommand.h"
#include "SymbolTable.h"

/**
 * The method calculates and returns the next index of the next line that in the vector s (from the Lexer).
 * Furthermore, the method calculates and updates the values of the variable that we want to change his value
 * (The variable is in s[i] and it is already exist in the 'NameToVar' map, and we just update its value).
 *
 * @param s - The vector of all the tokens from the Lexer.
 * @param i - The current index of the current line (In our case, our line changes a value of existing variable).
 * @return The index (int) of the next line in the vector. (If the we got the i that symbols the lase line,
 *         in the end of the algorithm, it returns s.size()).
 */
int SetCommand::execute(vector<string> s, int i) {
    //if we are here it means we are updating exisiting var
    //which means the value exists in nameToVar but ill check it anyway
    unordered_map<string, Var> nameToVar = SymbolTable::instance()->getNameToVar();
    if(nameToVar.find(s[i])!=nameToVar.end()) {
        // cout<<"inside2"<<endl;

        Interpreter* interp = new Interpreter(); // The object of the Interpreter class

        Expression* exp = nullptr; // The object of the Expression class

        string setVariablesStr = ""; // A string of the setVariables Method in the Interpreter class

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

        // cout<<"inside2.5"<<endl;

        // Calculate the value of the current variable (s[i]) by its mathematical expression
        interp->setVariables(setVariablesStr); // Set  the other variables values
        exp = interp->interpret(s[i + 2]); // The mathematical expression is in s[i + 2]
        double ans = exp->calculate(); // Calculate the value of the mathematical expression

        Var ansVar = nameToVar[s[i]]; // Var instance in order to update the value of the current variable (s[i])

        ansVar.setValue(ans);

        // Updating the  value of the variable s[i] in the NameToVar map
        SymbolTable::instance()->insertToNameToVar(s[i], ansVar);

        // If s[i] has had one of the arrows (-> OR <-) we will update its value in SimToVar map also
        if (ansVar.getHasDirection() == true) {
            //if the direction is "->"
            if(ansVar.getDirection()==1){
                //SymbolTable::instance()->setInstruction("");
                string instruction="";
                //concat the sim
                instruction+=ansVar.getSim();
                //remove the "/
                instruction.erase(0,2);
                instruction.pop_back();
                //insert "set
                string beg;
                instruction+=" ";
                ostringstream valAsStr;
                valAsStr <<ansVar.getValue();
                string finalStrValue = valAsStr.str();
                instruction+=finalStrValue;
                //beg+='"';
                beg+="set ";
                instruction.insert(0,beg);
                //instruction+='"';
                //concat the value
                instruction+="\r\n";
                SymbolTable::instance()->setInstruction(instruction);
                // SymbolTable::instance()->setLeftToSend(true);
                //insert into our instructions queue
                //  cout<<"setcommand "+instruction<<endl;
                // SymbolTable::instance()->insertToInstructions(instruction);
                //cout << "hereeeeeeeeeeeeeeee"+instruction << endl;
                // cout<<"inside3"<<endl;
                //   SymbolTable::instance()->setInstruction(instruction);
                // cout << (SymbolTable::instance()->getInstruction() << endl;
                // cout<<"inside4"<<endl;
            }
            else{
                SymbolTable::instance()->insertToSimToVar(ansVar.getSim(), ansVar);
            }
            //if we want without mutex lets send it to the simulator if it has direction-the server will update it

        }
        //cout<<"inside 5"<<endl;

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

        // If unusual something was wrong, and we did not suppose to arrive here, print error.
    else {
        cout<<"Error->setCommand.cpp->The var: '" + s[i] + "' is not exist in NameToVar map"<<endl;
        exit(0);
    }
}