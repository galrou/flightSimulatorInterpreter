//
// Created by idanbazel on 12/12/2019.
//

#include "Lexer.h"

using namespace std;


/**
 * The function puts into the field 'TokensVector' all the tokens that are in 'fileName'.
 * @param fileName - The path of the file (The file with the code-text)
 */
void Lexer::lexer(const string fileName) {

    string line; // The current line

    ifstream readFile(fileName); // The stream

    // If the file is not open
    if (!readFile) {
        cout<<"error: Lexer.cpp->lexing->openFile"<<endl;
        exit(0);
    }

    // Add any line to the vector
    while(!readFile.eof()) {
        // Put the current line into the string 'line'
        getline(readFile, line);

        string newStrLine = theFirstFix(line);

        // If we have not the empty string, keep going. Else, ignore that string.
        if (newStrLine != "") {
            // The line without spaces and tabs (almost without spaces)
            newStrLine = splitBySpacesAndTabs(newStrLine);

            // Divide the line to tokens and insert everything to field: 'TokensVector' of the class.
            splitByOperators(newStrLine);
        }
    }

    readFile.close();
}

/**
 * The method checks and erase all the empty strings or spaces and tabs in st and returns the fixed string.
 *
 * @param str - The string that we fix
 * @return 'st' - The string 'str' after fixing.
 */
string Lexer::theFirstFix(string str) {

    string st = str; // It will be vec[i]

    // Check and erase all the empty strings or spaces and tabs in vec[i] (st) and pushes back into 'ansVec'.

        if (st == "") {
            return str;
        }

        while (st[0] == ' ' || st[0] == '\t') {
            st.erase(0, 1);
        }

    return st;
}


/**
 *
 * @return The TokensVector
 */
vector<string> Lexer::getTokensVector() {
    return this->TokensVector;
}

/**
 *
 * @return A deep copy of the TokensVector
 */
vector<string> Lexer::getCopyTokensVector() {
    vector<string> immidiateTokensVector = getTokensVector(); // The TokensVector
    vector<string> copyTokensVector; // The copy vector that we will return
    int TokensVectorSize = immidiateTokensVector.size(); // The size of the TokensVector

    // Put all the tokens of the TokensArray into the copy array
    for (int index = 0; index < TokensVectorSize; index++) {
        copyTokensVector.push_back(immidiateTokensVector[index]);
    }

    return copyTokensVector;
}


/**
 * The method checks any string if it has a SPACE or TAB char and remove them out the string str.
 * (But the command 'Print' that gets a special case for the string that it prints).
 *
 * @param str - The string that we want to chaeck and change (if necessary).
 * @return The new string.
 */
string Lexer::splitBySpacesAndTabs(string str) {

    size_t start = 0; // The place of the start of the string that we will search in 'str'
    string st1 = str; // Get the 'str' parmeter
    string ans = ""; // The answer string that we will return

    // If the command is 'Print'-> A special treatment
    if (st1.find("Print") != std::string::npos) {
        //Remove tabs
        if((st1.find("\t")) != std::string::npos) {
            // Remove all The tabs
            while ((start = st1.find("\t")) != std::string::npos) {
                st1.erase(0, start + 1);
            }
        }
        return st1;
    }

    // If the command is 'while' loop-> A special treatment
    if (st1.find("while ") != std::string::npos) {
        //Remove tabs
        ans = "while ";
        start = st1.find("while ");
        st1.erase(0,start + 6);
    }

    // If the command is 'if' condition-> A special treatment
    if (st1.find("if ") != std::string::npos) {
        //  Remove tabs
        ans = "if ";
        start = st1.find("if ");
        st1.erase(0,start + 3);
    }

    // If the command is 'var' declaration-> A special treatment
    if (st1.find("var ") != std::string::npos) {
        // Remove tabs
        ans = "var ";
        start = st1.find("var ");
        st1.erase(0,start + 4);
    }

    // Remove spaces - The global case
    while ((start = st1.find(" ")) != std::string::npos) {

        ans += st1.substr(0, start);

        st1.erase(0, start + 1);
    }

    ans+=st1;

    // Remove tabs -> The global case
    st1 = ans;
    ans = "";
    while ((start = st1.find("\t")) != std::string::npos) {
        st1.erase(0, start + 1);
    }
    ans+=st1;

    return ans;
}

/**
 * The function splits the string 'str' by all the operators and what we need to get a vector of tokens,
 * and insert to the TokensVector field, all the tokens of the string 'str'.
 * @param str - The string that we will split
 */
void Lexer::splitByOperators(string str) {

    size_t start = 0; // The place of the start of the string that we will search in 'str'
    string st1 = str;;  // The string that we will split

    vector<string> ansVec; // The vector of the tokens for this 'str'

    // Now we are checking any case of operators.

    if (st1.find("->") != std::string::npos) {
        while ((start = st1.find("->")) != std::string::npos) {

            string ansPartStr = st1.substr(0, start);
            ansVec.push_back(ansPartStr);
            ansVec.push_back("->");
            st1.erase(0, start + 2);
        }
    }

    if (st1.find("!=") != std::string::npos) {
        while ((start = st1.find("->")) != std::string::npos) {

            string ansPartStr = st1.substr(0, start);
            ansVec.push_back(ansPartStr);
            ansVec.push_back("->");
            st1.erase(0, start + 2);
        }
    }

    if (st1.find("<-") != std::string::npos) {
        while ((start = st1.find("<-")) != std::string::npos) {

            string ansPartStr = st1.substr(0, start);
            ansVec.push_back(ansPartStr);
            ansVec.push_back("<-");
            st1.erase(0, start + 2);
        }
    }

    if (st1.find("==") != std::string::npos) {
        while ((start = st1.find("==")) != std::string::npos) {

            string ansPartStr = st1.substr(0, start);
            ansVec.push_back(ansPartStr);
            ansVec.push_back("==");
            st1.erase(0, start + 2);
        }
    }


    if (st1.find("<=") != std::string::npos) {
        while ((start = st1.find("<=")) != std::string::npos) {

            string ansPartStr = st1.substr(0, start);
            ansVec.push_back(ansPartStr);
            ansVec.push_back("<=");
            st1.erase(0, start + 2);
        }
    }

    if (st1.find(">=") != std::string::npos) {
        while ((start = st1.find(">=")) != std::string::npos) {

            string ansPartStr = st1.substr(0, start);
            ansVec.push_back(ansPartStr);
            ansVec.push_back(">=");
            st1.erase(0, start + 2);
        }
    }

    if (st1.find("<") != std::string::npos) {
        while ((start = st1.find("<")) != std::string::npos) {

            string ansPartStr = st1.substr(0, start);
            ansVec.push_back(ansPartStr);
            ansVec.push_back("<");
            st1.erase(0, start + 1);
        }
    }

    if (st1.find(">") != std::string::npos) {
        while ((start = st1.find(">")) != std::string::npos) {

            string ansPartStr = st1.substr(0, start);
            ansVec.push_back(ansPartStr);
            ansVec.push_back(">");
            st1.erase(0, start + 1);
        }
    }

    if (st1.find("=") != std::string::npos) {
        while ((start = st1.find("=")) != std::string::npos) {

            string ansPartStr = st1.substr(0, start);
            ansVec.push_back(ansPartStr);
            ansVec.push_back("=");
            st1.erase(0, start + 1);
        }
    }


    ansVec.push_back(st1);

    string varTreatment = ansVec[0]; // Check special cases (var, if, while...)

    // Refer to 'var name' or 'while codition' or 'if condition'
    if (varTreatment.find("var") != std::string::npos) {
        if (varTreatment.length() >= 4) {
            if (varTreatment[3] == ' ') {
                varTreatment.erase(0, 4);

                ansVec[0] = "var";
                ansVec.push_back(ansVec[ansVec.size() - 1]);

                for (int j = ansVec.size() - 2; j >= 1; j--) {
                    ansVec[j + 1] = ansVec[j];
                }

                ansVec[1] = varTreatment;
            }
        }
    } else if (varTreatment.find("if") != std::string::npos) {
        if (varTreatment.length() >= 3) {
            if (varTreatment[2] == ' ') {
                varTreatment.erase(0, 3);

                ansVec[0] = "if";
                ansVec.push_back(ansVec[ansVec.size() - 1]);

                for (int j = ansVec.size() - 2; j >= 1; j--) {
                    ansVec[j + 1] = ansVec[j];
                }

                ansVec[1] = varTreatment;
            }
        }
    } else if (varTreatment.find("while") != std::string::npos) {
        if (varTreatment.length() >= 6) {
            if (varTreatment[5] == ' ') {
                varTreatment.erase(0, 6);

                ansVec[0] = "while";
                ansVec.push_back(ansVec[ansVec.size() - 1]);

                for (int j = ansVec.size() - 2; j >= 1; j--) {
                    ansVec[j + 1] = ansVec[j];
                }

                ansVec[1] = varTreatment;
            }
        }
    }

    ansVec = fixTokens(ansVec);
    ansVec.push_back(";EOL;"); // Push 'End of Line' symbol to know that we finished with the current line.

    // Pass all the tokens of 'str' into the field TokensVector
    for (unsigned int k = 0; k < ansVec.size(); k++) {
        this->TokensVector.push_back(ansVec[k]);
    }
}

/**
 * The function fix the tokens of the vector.
 * @param vec The vector
 * @return A new vector with fix tokens
 */
vector<string> Lexer::fixTokens(vector<string> vec) {

    // If we have 'while' or 'if'
    if ((vec[0].compare("while") == 0) || (vec[0].compare("if") == 0)) {
        return fixWhileOrIfCondition(vec);
    }

    // If we have something with brackets that we need to split
    if (isContainSpecialCommandWithBrackets(vec)) {
        return fixSpecialCommandsWithBrackets(vec);
    }

    return vec;
}

/**
 *
 * @param vec A vector of tokens
 * @return True - If we have something that needs to get a "brackets tretment", False - Otherwise.
 */
bool Lexer::isContainSpecialCommandWithBrackets(vector<string> vec) {

    // Check all the tokens in the vector 'vec'
    for (unsigned int i = 0; i < vec.size(); i++) {
        string vecI = vec[i];
        if (isContainStr(vecI, "sim(") || isContainStr(vecI, "Print(") || isContainStr(vecI, "Sleep(")
        || isContainStr(vecI, "openDataServer(") || isContainStr(vecI, "connectControlClient(")) {
            return true;
        }
    }
    return false;
}

/**
 *
 * @param source The source string
 * @param target The string that we want to check if it is contained the  string 'source'
 * @return True - If source contains target. False - Otherwise.
 */
bool Lexer::isContainStr(string source, string target) {
    if (source.find(target) != std::string::npos) {
        return true;
    }
    return false;
}


/**
 * The function fixes the special commands with brackets that need a divison to new tokens.
 * @param vec A vector of tokens
 * @return The new vector with fix tokens
 */
vector<string> Lexer::fixSpecialCommandsWithBrackets(vector<string> vec) {

    size_t start = 0; // The start position in any match
    vector<string> ans; // The new fixed vector
    string vecI = ""; // Get the vec[i] element
    string currentStr = ""; // The current part of string any iteration

    // Check all the elements and fix them if we need
    for (unsigned int i = 0; i < vec.size(); i++) {
        vecI = vec[i];
        currentStr = "";

        // If we have the command 'sim(...)'
        if (vec[i].find("sim(") != std::string::npos) {

            ans.push_back("sim");
            for (unsigned int j = 4; j < vecI.size()-1; j++) {
                currentStr += vecI[j];
            }
            ans.push_back(currentStr);
        }
        else {

            // If we have the command 'Print(...)'
            if (vec[i].find("Print(") != std::string::npos) {

                ans.push_back("Print");
                for (unsigned int j = 6; j < vecI.size()-1; j++) {
                    currentStr += vecI[j];
                }
                ans.push_back(currentStr);
            } else {

                // If we have the command 'Sleep(...)'
                if (vec[i].find("Sleep(") != std::string::npos) {

                    ans.push_back("Sleep");
                    for (unsigned int j = 6; j < vecI.size()-1; j++) {
                        currentStr += vecI[j];
                    }
                    ans.push_back(currentStr);
                } else {

                    // If we have the command 'openDataServer(...)'
                    if (vec[i].find("openDataServer(") != std::string::npos) {

                        ans.push_back("openDataServer");
                        for (unsigned int j = 15; j < vecI.size()-1; j++) {
                            currentStr += vecI[j];
                        }
                        ans.push_back(currentStr);
                    } else {

                        // If we have the command 'connectControlClient(...)'
                        if ((start = vec[i].find("connectControlClient(")) != std::string::npos) {

                            ans.push_back("connectControlClient");
                            vecI.erase(0, start + 21);
                            //Split and insert the IP and the PORT number into the vector 'ans' as two different strings
                            if ((start = vecI.find(",")) != std::string::npos) {
                                string ip = vecI.substr(0, start) + "\"";
                                ans.push_back(ip);

                                vecI.erase(0,start + 1); // Erase (plus the: ,)
                                vecI.erase(vecI.length() - 1, 1); // Erase the )

                                string port = "\"" + vecI;
                                ans.push_back(port);
                            }

                        } else {
                            ans.push_back(vec[i]);
                        }
                    }
                }
            }
        }
    }
    return ans;
}

/**
 * The function fix 'while' loop or 'if' condition in the part with: ...'someString{'..., to be ...'someString', '{'...
 * @param vec - The vector that we want to fix.
 * @return A new vector with the fixed tokens.
 */
vector<string> Lexer::fixWhileOrIfCondition(vector<string> vec) {

    vector<string> ans; // The fixed vector


    for (unsigned int i = 0; i < vec.size(); i++) {
        string currentStr = ""; // A string for the 'someString'

        // If we have a string with '{' (it will be: 'someString{') so split that.
        if (vec[i].find("{") != std::string::npos) {

            // Chain all the someString but the char '{'.
            for (unsigned int j = 0; j < vec[i].length() - 1; j++) {
                currentStr += (vec[i])[j];
            }
            ans.push_back(currentStr);
            ans.push_back("{");
            currentStr = "";

        } else {
            ans.push_back(vec[i]);
        }
    }

    return ans;
}