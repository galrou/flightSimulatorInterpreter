//
// Created by idanbazel on 16/12/2019.
//

#ifndef FLIGHTSIMULATOR_EXPRESSIONCLASS_H
#define FLIGHTSIMULATOR_EXPRESSIONCLASS_H


class ExpressionClass {

};

#include "Expression.h"
#include <regex>
#include <string>
#include <stack>
#include <queue>
#include <map>
#include <string>

enum type {OPERATOR, NUMBER, VARIABLE, OPEN_BRACE, CLOSE_BRACE};

using namespace std;


class ex1 {
};

//--------------------------------------------
class UnaryOperator:public Expression {
protected:
    Expression* exp;

public:
    UnaryOperator(Expression*);
    ~UnaryOperator();
};

//--------------------------------------------
class BinaryOperator:public Expression {
protected:
    Expression* right;
    Expression* left;

public:
    BinaryOperator(Expression*, Expression*);
    ~BinaryOperator();
};

//--------------------------------------------
class UPlus:public UnaryOperator {

public:
    UPlus(Expression* exp);
    ~UPlus();
    double calculate();
};

//--------------------------------------------
class UMinus:public UnaryOperator {

public:
    UMinus(Expression* exp);
    ~UMinus();
    double calculate();
};

//--------------------------------------------
class Plus: public BinaryOperator {

public:
    Plus(Expression* right, Expression* left);
    ~Plus();
    double calculate();
};

//--------------------------------------------
class Minus:public BinaryOperator {

public:
    Minus(Expression* right, Expression* left);
    ~Minus();
    double calculate();
};

//--------------------------------------------
class Mul:public BinaryOperator {

public:
    Mul(Expression* right, Expression* left);
    ~Mul();
    double calculate();
};

//--------------------------------------------
class Div:public BinaryOperator {

public:
    Div(Expression*, Expression*);
    ~Div();
    double calculate();
};

//--------------------------------------------
class Value:public Expression {

    double val;

public:
    Value(double);
    ~Value();
    double calculate();
};

//--------------------------------------------
class Variable:public Expression {

    string name;
    double value;

public:
    Variable(string, double);
    double calculate();
    Variable& operator++();
    Variable& operator--();
    Variable& operator+=(double);
    Variable& operator-=(double);
    Variable& operator++(int);
    Variable& operator--(int);
    ~Variable();
};


class TypeString {

private:
    string str;
    type t;

public:

    TypeString(string);
    string getStr();
    void setType(type);
    type getType();
    bool isNum(char);
};


class Interpreter {
    stack<TypeString> operatorsStack;
    queue<TypeString> numbersQueue;
    queue<TypeString> tokensQueue;
    map<string, string> variablesMap;
    string str;

public:
    Interpreter();
    ~Interpreter();
    stack<TypeString> getOperatorsStack();
    queue<TypeString> getNumbersQueue();
    queue<TypeString> getTokensQueue();
    string getStrExpression();
    vector<TypeString> makeTokensVector();
    void preProcessingTokens();
    void shuntingYardAlgorithm();
    Expression* interpret(string);
    void setVariables(string);
    vector<TypeString> convertVariablesToValues(vector<TypeString>);
    bool isExistInVariablesMap(string);
    string getValueOfVarsMapByKey(string);
    void isValidVarsInputSetVars();
    bool isValidVariable(string);
    bool isValidNumber(string);
    void checkBrackets();
    void checkInfixValidation();
    bool isNumber(char);
    bool isVariable(char);
    int getNumberVariableSubString(string, int);
    int getNumberSubString(string, int);
    string getSubString(string, int, int);
};


#endif //FLIGHTSIMULATOR_EXPRESSIONCLASS_H
