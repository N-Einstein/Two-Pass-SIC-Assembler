//
// Created by Lenovo on 5/3/2017.
//

#ifndef ASSEMBLERSIC_WRONGCOMM_H
#define ASSEMBLERSIC_WRONGCOMM_H


#include "Command.h"

class wrongComm : public Command{
public:
    wrongComm(string l, string error);
    string getComment();
    string getLine();
    string calculate(int s, string code, string sympol);
    int getLength();
    void setStatus(int s);
    void setLength(int l);
    void setOpcode(string op);
    string getSym();
    int getStatus();
    string getOpcode();
    void setSym(string s);
    void setLabel(string s);
    string getLabel();
    void setOperator(string s);
    void appendComment(string obj);
    string getOperator();

private:
    string comment = "", l;

};


#endif //ASSEMBLERSIC_WRONGCOMM_H
