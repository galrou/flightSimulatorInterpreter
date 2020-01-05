//
// Created by idanbazel on 16/12/2019.
//

#include <iostream>
#include "ExpressionClass.h"

/************************************
 * UnaryOperator
 ************************************
 */
 /**
  * A constructor.
  * @param exp1 - The expression
  */
UnaryOperator::UnaryOperator(Expression *exp1) {
    this->exp = exp1;
}

/**
 * A destructor
 */
UnaryOperator::~UnaryOperator() {
    delete this->exp;
}

/************************************
 * BinaryOperator
 ************************************
 */
 /**
  * A constructor.
  *
  * @param left1 - The right expression
  * @param right1 - The left expression
  */
BinaryOperator::BinaryOperator(Expression *left1, Expression *right1) {
    this->right = right1;
    this->left = left1;
}

/**
 * A destructor
 */
BinaryOperator::~BinaryOperator() {
    delete this->right;
    delete this->left;
}

/************************************
 * UPlus
 ************************************
 */
/**
* A constructor.
*
* @param exp1 - The expression
*/
UPlus::UPlus(Expression *exp1) : UnaryOperator(exp1) {

}

/**
 *
 * @return The calculated expression
 */
double UPlus::calculate() {
    return this->exp->calculate();
}

/**
 * A destructor
 */
UPlus::~UPlus() {
}

/************************************
 * UMinus
 ************************************
 */
/**
* A constructor.
*
* @param exp1 - The expression
*/
UMinus::UMinus(Expression *exp1) : UnaryOperator(exp1) {

}

/**
 *
 * @return The calculated expression
 */
double UMinus::calculate() {
    return -1.0 * this->exp->calculate();
}

/**
 * A destructor.
 */
UMinus::~UMinus() {
}

/************************************
 * Plus
 ************************************
 */
Plus::Plus(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {

}

/**
 *
 * @return The calculated value
 */
double Plus::calculate() {
    return this->left->calculate() + this->right->calculate();
}

/**
 * A destructor.
 */
Plus::~Plus() {
}

/************************************
 * Minus
 ************************************
 */
/**
* A constructor.
*
* @param left1 - The right expression
* @param right1 - The left expression
*/
Minus::Minus(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {

}

/**
 *
 * @return The calculated value
 */
double Minus::calculate() {
    return this->left->calculate() - this->right->calculate();
}

/**
 * A destructor.
 */
Minus::~Minus() {
}

/************************************
 * Mul
 ************************************
 */
/**
* A constructor.
*
* @param left1 - The right expression
* @param right1 - The left expression
*/
Mul::Mul(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {

}

/**
 *
 * @return The calculated value
 */
double Mul::calculate() {
    return 1.0 * this->left->calculate() * this->right->calculate();
}

/**
 * A destructor.
 */
Mul::~Mul() {
}

/************************************
 * Div
 ************************************
 */
/**
* A constructor.
*
* @param left1 - The right expression
* @param right1 - The left expression
*/
Div::Div(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {

}

/**
 *
 * @return The calculated value
 */
double Div::calculate() {

    if (this->right->calculate() == 0.0) {
        throw "you divide by 0";
    } else
        return this->left->calculate() / this->right->calculate();
}

/**
 * A destructor.
 */
Div::~Div() {
}

/************************************
 * Value
 ************************************
 */
/**
* A constructor.
*
* @param val1 - The value
*/
Value::Value(double val1) {
    this->val = val1;
}

/**
 *
 * @return The current value
 */
double Value::calculate() {
    return this->val;
}

/**
 * A destructor.
 */
Value::~Value() {
}

/************************************
 * Variable
 ************************************
 */
 /**
  * A constructor.
  *
  * @param name1 - The variable name
  * @param value1 - The variable's value
  */
Variable::Variable(string name1, double value1) {
    this->name = name1;
    this->value = value1;
}

/**
 *
 * @return The calculated value
 */
double Variable::calculate() {
    return this->value;
}

/**
 *
 * @return The variable after ++ operator.
 */
Variable &Variable::operator++() {
    ++(this->value);
    return *this;
}

/**
 *
 * @return The variable after ++ operator (Overloading).
 */
Variable &Variable::operator++(int) {
    (this->value)++;
    return *this;
}

/**
 *
 * @return The variable after += operator.
 */
Variable &Variable::operator+=(double num) {
    (this->value) += num;
    return *this;
}

/**
 *
 * @return The variable after -= operator.
 */
Variable &Variable::operator-=(double num) {
    (this->value) -= num;
    return *this;
}

/**
 *
 * @return The variable after -- operator.
 */
Variable &Variable::operator--() {
    --(this->value);
    return *this;
}

/**
 *
 * @return The variable after -- operator.
 */
Variable &Variable::operator--(int) {
    (this->value)--;
    return *this;
}

/**
 * A destructor.
 */
Variable::~Variable() {
}


/************************************
* TypeString
************************************
*/
/**
 *
 * @param c - The character
 * @return True - when 'c' is a number, False - otherwise
 */
bool TypeString::isNum(char c) {
    // The method gets a char c and returns true - If we c is a number or part of number, and returns false - Otherwise.
    switch (c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
            return true;
        default:
            return false;
    }
}

/**
 * The method changes the type of the string.
 *
 * @param newType - The new type
 */
void TypeString::setType(type newType) {
    this->t = newType;
}

/**
 * A constructor.
 * @param str1 - The string
 */
TypeString::TypeString(string str1) {
    this->str = str1;
    if ((str1.compare("+") == 0) || (str1.compare("-") == 0) || (str1.compare("*") == 0) || (str1.compare("/") == 0)) {
        this->t = OPERATOR;
    } else {
        if (str1.compare("(") == 0) {
            this->t = OPEN_BRACE;
        } else {
            if (str1.compare(")") == 0) {
                this->t = CLOSE_BRACE;
            } else {
                if (isNum(str1[0]) == true) {
                    if (str1[0] == '.') {
                        throw "error";
                    } else {
                        this->t = NUMBER;
                    }
                } else {
                    this->t = VARIABLE;
                }
            }
        }
    }
}

/**
 *
 * @return The current string
 */
string TypeString::getStr() {
    return this->str;
}

/**
 *
 * @return The current type
 */
type TypeString::getType() {
    return this->t;
}

/************************************
 * Interpreter
 ************************************
 */
 /**
  * A constructor.
  */
Interpreter::Interpreter() {
}

/**
 * A destructor.
 */
Interpreter::~Interpreter() {

}

/**
 *
 * @return The queue of the numbers
 */
queue<TypeString> Interpreter::getNumbersQueue() {
    return this->numbersQueue;
}

/**
 *
 * @return The stack of the operators
 */
stack<TypeString> Interpreter::getOperatorsStack() {
    return this->operatorsStack;
}

/**
 *
 * @return The tokens queue
 */
queue<TypeString> Interpreter::getTokensQueue() {
    return this->tokensQueue;
}

/**
 *
 * @return The expression as a string
 */
string Interpreter::getStrExpression() {
    return this->str;
}

/**
 *
 * @param c - The character
 * @return True - when 'c' is a number, False - otherwise
 */
bool Interpreter::isNumber(char c) {
    // The method gets a char c and returns true - If we c is a number or part of number, and returns false - Otherwise.
    switch (c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
            return true;
        default:
            return false;
    }
}

/**
 *
 * @param c  - A character
 * @return True - 'c' is variable, False - o.w.
 */
bool Interpreter::isVariable(char c) {
    // The method gets a char c and returns true - If c is a variable, and returns false - Otherwise.
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'));
}

/**
 *
 * @param st - The string
 * @param place - The place
 * @return The number of the variables in st
 */
int Interpreter::getNumberVariableSubString(string st, int place) {
    // The method gets string st and int place, and returns the place of the last char that is a number.
    int i = 0;
    int sLen = st.length();
    for (i = place; i < sLen; i++) {
        if (isVariable(st[i]) == false) {
            if ((isNumber(st[i]) == false) || (st[i] == '.')) {
                break;
            }
        }
    }
    return (i - 1);
}

/**
 *
 * @param st - The string
 * @param place - The place
 * @return The method gets string st and int place, and returns the place of the last char that is a number.
 */
int Interpreter::getNumberSubString(string st, int place) {

    int i = 0;
    int sLen = st.length();
    for (i = place; i < sLen; i++) {
        if (isNumber(st[i]) == false) {
            break;
        }
    }
    return (i - 1);
}

/**
 *
 * @param st  - The string
 * @param start - The start
 * @param end - The end
 * @return The method gets string st and int place, and returns the string that its last char is a number (from 'start').
 */
string Interpreter::getSubString(string st, int start, int end) {

    string ans = "";
    for (int i = start; i <= end; i++) {
        ans += st[i];
    }
    return ans;
}

/**
 *
 * @return The method returns a vector with all the tokens
 */
vector<TypeString> Interpreter::makeTokensVector() {
    string st = this->getStrExpression();
    vector<TypeString> v;
    int sLen = st.length();
    for (int i = 0; i < sLen; i++) {
        // If we have an operator
        if ((st[i] == '+') || (st[i] == '-') || (st[i] == '*') || (st[i] == '/') || (st[i] == '(') || (st[i] == ')')) {
            string s = string(1, st[i]);
            TypeString *ans = new TypeString(s);
            v.push_back(*ans);
        }
            // If we have not an operator
        else {
            // If we have a number
            if (isNumber(st[i]) == true) {
                int end = getNumberSubString(st, i);
                string s = getSubString(st, i, end);
                TypeString *ans = new TypeString(s);
                v.push_back(*ans);
                i = end;
            }
                // If we have not a number
            else {
                // If we have a variable
                if (isVariable(st[i]) == true) {
                    int end = getNumberVariableSubString(st, i);
                    string s = getSubString(st, i, end);
                    TypeString *ans = new TypeString(s);
                    v.push_back(*ans);
                    i = end;
                }
                    // Not operator, number or variable => Invalid Input
                else {
                    throw "Invalid input";
                }
            }
        }
    }


    v = convertVariablesToValues(v);

    return v;
}

/**
 *
 * @param s - The string
 * @return True - The variable exists in the map, False - Otherwise.
 */
bool Interpreter::isExistInVariablesMap(string s) {

    for (auto it = this->variablesMap.begin(); it != this->variablesMap.end(); it++) {
        string var = it->first;

        if (var.compare(s) == 0) {
            return true;
        }
    }
    return false;
}

/**
 *
 * @param s - The string
 * @return The values of vars in the map by keys
 */
string Interpreter::getValueOfVarsMapByKey(string s) {

    string ans = "";
    bool weSawTheVariable = false;

    for (auto it = this->variablesMap.begin(); it != this->variablesMap.end(); it++) {
        string var = it->first;

        if (var.compare(s) == 0) {
            ans = it->second;
            weSawTheVariable = true;
        }
    }
    if (weSawTheVariable == false) {
        throw "Variable is not exist.";
    }
    return ans;
}

/**
 *
 * @param v - The vector
 * @return The converted variables to values in a vector
 */
vector<TypeString> Interpreter::convertVariablesToValues(vector<TypeString> v) {

    queue<TypeString> ansQ;
    int sLen = v.size();
    for (int i = 0; i < sLen; i++) {

        TypeString ts = v.at(i);

        if (ts.getType() == VARIABLE) {

            if (isExistInVariablesMap(ts.getStr())) {

                TypeString *newTS = new TypeString(getValueOfVarsMapByKey(ts.getStr()));
                newTS->setType(NUMBER);
                ansQ.push(*newTS);

            } else {
                throw "Operator is not exist.";
            }
        } else {
            ansQ.push(ts);
        }
    }

    int j = 0;

    while (!ansQ.empty()) {
        v.at(j) = ansQ.front();
        ansQ.pop();
        j++;
    }

    return v;
}

/**
 * The method puts zero each place that we want to cast an unary operator to binary operator.
 */
void Interpreter::preProcessingTokens() {

    vector<TypeString> v = this->makeTokensVector();
    vector<TypeString> preAns;
    int sLen = v.size();
    for (int i = 0; i < sLen; i++) {
        if (i == 0) {
            if ((v.at(i).getStr().compare("+") == 0) || v.at(i).getStr().compare("-") == 0) {
                preAns.push_back(*(new TypeString("0")));
            }
            preAns.push_back(v.at(i));
            continue;
        }

        if (i < sLen - 1) {

            if ((v.at(i).getStr().compare("+") == 0) || v.at(i).getStr().compare("-") == 0) {

                if ((v.at(i + 1).getType() == OPEN_BRACE) && (v.at(i - 1).getType() != VARIABLE) &&
                    (v.at(i - 1).getType() != NUMBER)) {
                    preAns.push_back(*(new TypeString("0")));
                } else {
                    if (((v.at(i + 1).getType() == NUMBER) || (v.at(i + 1).getType() == VARIABLE)) &&
                        (v.at(i - 1).getType() == OPEN_BRACE)) {
                        preAns.push_back(*(new TypeString("0")));
                    }
                }

            }
            preAns.push_back(v.at(i));
            continue;
        }

        preAns.push_back(v.at(i));
    }

    // Pass all the arguments to the tokensQueue
    int pLen = preAns.size();
    for (int j = 0; j < pLen; j++) {
        this->tokensQueue.push(preAns.at(j));
    }

}

/**
 * The Shunting-Yard algorithm
 */
void Interpreter::shuntingYardAlgorithm() {


    this->preProcessingTokens(); // Pre-Processing

    checkInfixValidation();

    queue<TypeString> copyTokensQueue = this->tokensQueue;


    while (!copyTokensQueue.empty()) {

        TypeString e = copyTokensQueue.front();
        copyTokensQueue.pop();

        if (e.getType() == NUMBER) {
            if (!isValidNumber(e.getStr())) {
                throw "Invalid number.";
            }
            numbersQueue.push(e);
        }
        if (e.getType() == VARIABLE) {
            if (!isValidVariable(e.getStr())) {
                throw "Invalid number.";
            }
            numbersQueue.push(e);
        }
        if (e.getType() == OPERATOR) {

            while (!operatorsStack.empty() && ((e.getStr().compare("+") == 0 || e.getStr().compare("-") == 0) &&
                                               (operatorsStack.top().getType() == OPERATOR))) {

                numbersQueue.push(operatorsStack.top());
                operatorsStack.pop();
            }
            operatorsStack.push(e);
        }
        if (e.getType() == OPEN_BRACE) {
            operatorsStack.push(e);
        }
        if (e.getType() == CLOSE_BRACE) {

            while (operatorsStack.top().getType() != OPEN_BRACE) {

                numbersQueue.push(operatorsStack.top());
                operatorsStack.pop();
            }
            operatorsStack.pop();
        }
    }


    while (!operatorsStack.empty()) {

        numbersQueue.push(operatorsStack.top());
        operatorsStack.pop();
    }
}


/**
 *
 * @param st - The string
 * @return The interpred string as an Expression* type.
 */
Expression *Interpreter::interpret(string st) {


    this->str = st;

    checkBrackets();

    this->shuntingYardAlgorithm();

    Expression *exp;
    stack<TypeString> s;


    while (!this->numbersQueue.empty()) {

        TypeString obj = this->numbersQueue.front();
        if (obj.getType() == NUMBER) {
            if (!isValidNumber(obj.getStr())) {
                throw "Invalid number.";
            }
            s.push(obj);
        }

        if (obj.getType() == OPERATOR) {

            double right = stod(s.top().getStr());
            s.pop();
            double left = stod(s.top().getStr());
            s.pop();

            if (obj.getStr().compare("+") == 0)
                s.push(to_string(left + right));

            if (obj.getStr().compare("-") == 0)
                s.push(to_string(left - right));

            if (obj.getStr().compare("*") == 0)
                s.push(to_string(left * right));

            if (obj.getStr().compare("/") == 0) {
                if (right == 0.0) {
                    throw "Yow tried to divide by 0.";
                }
                s.push(to_string(1.0 * left / right));
            }
        }

        this->numbersQueue.pop();
    }

    double ansValue = stod(s.top().getStr());
    exp = new Value(ansValue);

    return exp;
}

/**
 * The method sets the variables in the string 'st'.
 * @param st - The string
 */
void Interpreter::setVariables(string st) {
    string st1 = st;
    string token;
    size_t start = 0;


    if (st1 != "") {
        if (st1[st1.length() - 1] != ';') {
            st1 = st1 + ";";
        }
        while ((start = st1.find(";")) != std::string::npos) {
            // cout<<st1<<endl;
            token = st1.substr(0, start);
            regex reg("[a-zA-Z_]+[a-zA-Z0-9_]*={1}[+-]?\\d*\\.?\\d+");
            if (!regex_match(token, reg)) {
                throw "Invalid input.";
            }
            int i = 0;
            int tokLen = token.length();
            for (i = 0; i < tokLen; i++) {
                if (token[i] == '=') {
                    break;
                }
            }
            string varName = "";
            string varValueHelper = "";
            int tokLen1 = token.length();

            for (int j = 0; j < tokLen1; j++) {
                if (j < i) {
                    varName = varName + token[j];
                }
                if (j > i) {
                    varValueHelper = varValueHelper + token[j];
                }
            }

            this->variablesMap[varName] = varValueHelper;

            st1.erase(0, start + 1);
        }

        // Checking if all the variables we got are valid
        isValidVarsInputSetVars();
    }
}

/**
 * The method checks if our input in 'setVariables' is valid.
 */
void Interpreter::isValidVarsInputSetVars() {

    for (auto it = this->variablesMap.begin(); it != this->variablesMap.end(); it++) {
        string var = it->first;
        string num = it->second;

        if (!isValidVariable(var)) {
            throw "The variable is not valid.";
        }

        if (!isValidNumber(num)) {
            throw "The number is not valid.";
        }
    }
}

/**
 *
 * @param var - The string
 * @return True - if the variable is valid, False - o.w.
 */
bool Interpreter::isValidVariable(string var) {
    regex regVar("[a-zA-Z_]+[a-zA-Z0-9_]*");
    return regex_match(var, regVar);
}

/**
 *
 * @param var - The string
 * @return True - if 'var' is a valid number, False - o.w.
 */
bool Interpreter::isValidNumber(string var) {
    regex regNum(R"(^([+-]?(?:[[:d:]]+\.?|[[:d:]]*\.[[:d:]]+))(?:[Ee][+-]?[[:d:]]+)?$)");
    return regex_match(var, regNum);
}

/**
 * The method checks the brackets of the expression.
 */
void Interpreter::checkBrackets() {
    stack<char> stk;
    queue<char> que;
    int rightCtr = 0, leftCtr = 0;
    int sLen = (this->str).length();
    for (int i = 0; i < sLen; i++) {
        if (this->str[i] == '(') {
            leftCtr++;
            que.push(this->str[i]);
        }
        if (this->str[i] == ')') {
            rightCtr++;
            que.push(this->str[i]);
        }
    }

    if (rightCtr != leftCtr) {
        throw "Invalid brackets.";
    }

    while (!que.empty()) {

        if (que.front() == ')') {
            if (stk.empty()) {
                throw "Invalid Brackets";
            } else {
                stk.pop();
                que.pop();
            }
        } else {
            stk.push(que.front());
            que.pop();
        }
    }

    if (!stk.empty()) {
        throw "Invalid Brackets";
    }
}

/**
 * The method checks the infix-validation of our expression.
 */
void Interpreter::checkInfixValidation() {

    queue<TypeString> helper;

    if (!this->tokensQueue.empty()) {
        if (this->tokensQueue.front().getStr().compare("*") == 0 ||
            this->tokensQueue.front().getStr().compare("/") == 0) {
            throw "Invalid input0";
        }

        while (!this->tokensQueue.empty()) {
            TypeString ts = this->tokensQueue.front();
            helper.push(ts);
            this->tokensQueue.pop();

            type tp = ts.getType();

            if (this->tokensQueue.empty()) {
                if (tp == OPERATOR || tp == OPEN_BRACE) {
                    throw "Invalid input1";
                }
                break;
            }

            if (tp == OPERATOR) {
                if (this->tokensQueue.front().getType() == OPERATOR ||
                    this->tokensQueue.front().getType() == CLOSE_BRACE) {
                    throw "Invalid input2";
                }
            }

            if (tp == OPEN_BRACE) {
                if (this->tokensQueue.front().getType() == CLOSE_BRACE ||
                    this->tokensQueue.front().getStr().compare("*") == 0 ||
                    this->tokensQueue.front().getStr().compare("/") == 0) {
                    throw "Invalid input3";
                }
            }

            if (tp == NUMBER || tp == VARIABLE) {
                if (this->tokensQueue.front().getType() == NUMBER || this->tokensQueue.front().getType() == VARIABLE ||
                    this->tokensQueue.front().getType() == OPEN_BRACE) {
                    throw "Invalid input4";
                }
            }

            if (tp == CLOSE_BRACE) {
                if (this->tokensQueue.front().getType() == OPEN_BRACE ||
                    this->tokensQueue.front().getType() == NUMBER ||
                    this->tokensQueue.front().getType() == VARIABLE) {
                    throw "Invalid input5";
                }
            }
        }

        while (!helper.empty()) {
            this->tokensQueue.push(helper.front());
            helper.pop();
        }
    }
}