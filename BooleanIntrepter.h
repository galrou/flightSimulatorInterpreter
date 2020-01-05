//
// Created by gal on 18/12/2019.
//

#ifndef FLIGHTSIMULATOR_BOOLEANINTREPTER_H
#define FLIGHTSIMULATOR_BOOLEANINTREPTER_H


#include <string>
#include "Expression.h"
#include "ExpressionClass.h"

using namespace std;
/**
 * checks whether a boolena expression is true or false
 */
class BooleanIntrepter {
public:
    int intereptCondition(Expression* left,string op,Expression*right){

        if(op=="=="){
            // exp= new EvenOp(left,right);
            return left->calculate() == right->calculate();
        }
        else if(op=="<"){
            return left->calculate() < right->calculate();

        }
        else if(op==">"){
            return left->calculate() > right->calculate();

        }
        else if(op=="<="){
            return left->calculate() <= right->calculate();

        }
        else if(op==">="){
            return left->calculate() >= right->calculate();

        }
        return left->calculate() != right->calculate();
    };


};


#endif //FLIGHTSIMULATOR_BOOLEANINTREPTER_H