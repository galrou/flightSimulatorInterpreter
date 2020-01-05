//
// Created by gal on 19/12/2019.
//

#ifndef FLIGHTSIMULATOR_VAR_H
#define FLIGHTSIMULATOR_VAR_H

#include <string>

using namespace std;
/**
 * a Var class this class is the variables we get in the file we read
 */
class Var {
private:
    //1 for right 0 for left
    bool direction;
    double value;
    string name;
    string sim;
    bool hasDirection;
public:
    Var(){
        sim="";
        name="";
        value=0;
        hasDirection=false;
    };
    /**
     * sets a directon of a variable
     * @param dir
     */
    void setDirection(string dir){
        if(dir=="->"){
            direction=1;
        }
        else{
            direction=0;
        }
        hasDirection=true;
    };
    /**
     * sets the value of a variable
     * @param val
     */
    void setValue(double val){
        value=val;
    };
    /**
     * sets the sim of a variable
     * @param sim1
     */
    void setSim(string sim1){
        sim=sim1;
    };
    /**
     * sets the name of a variable
     * @param name1
     */
    void setName(string name1){
        name=name1;
    }
    /**
     * returns the value of a variabe
     * @return
     */
    double getValue() {
        return this->value;
    }
    /**
     * return the name of a variable
     * @return
     */
    string getName() {
        return this->name;
    }
    /**
     * returns the sim of a variable
     * @return
     */
    string getSim() {
        return this->sim;
    }
    /**
     * returns true if a variable has adirection
     * @return
     */
    bool getHasDirection() {
        return this->hasDirection;
    }
    /**
     * return the direction of a avriable
     * @return
     */
    int getDirection(){
        return direction;
    }
};

#endif //FLIGHTSIMULATOR_VAR_H