//
// A class for the Lexer.
// Created by idanbazel on 12/12/2019.
//

#ifndef FLIGHTSIMULATOR_LEXER_H
#define FLIGHTSIMULATOR_LEXER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>


using namespace std;

// A class for the lexer
class Lexer {

private:
    vector<string> TokensVector; // The vector of the strings

public:
    // Constructor
    Lexer() {}

    // A function for lexing the file
    void lexer(string);

    // Split and fix methods for the text that the lexer will get.

    void splitByOperators(string);
    string splitBySpacesAndTabs(string);
    vector<string> fixTokens(vector<string>);
    vector<string> fixSpecialCommandsWithBrackets(vector<string>);
    vector<string> fixWhileOrIfCondition(vector<string>);
    bool isContainSpecialCommandWithBrackets(vector<string>);
    bool isContainStr(string, string);
    string theFirstFix(string);

    // Getters for the field 'TokensVector'
    vector<string> getTokensVector();
    vector<string> getCopyTokensVector();
};


#endif //FLIGHTSIMULATOR_LEXER_H
