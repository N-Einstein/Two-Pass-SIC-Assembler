//
// Created by Lenovo on 4/15/2017.
//

#ifndef UNTITLED222_INSTRUCTION_H
#define UNTITLED222_INSTRUCTION_H


#include "Command.h"

class Instruction : public Command{
public:
    Instruction();
    string calculate(int s, string code, string sympol);
    int getLength();
    void setStatus(int s);
    void setOpcode(string op);
    int getStatus();
    void setSym(string s);
    string getSym();
    string getOpcode();
    void setLabel(string s);
    string getLabel();
    void setOperator(string s);
    string getOperator();
    string getComment();
    string getLine();
    void setObjectCode(string obj);
    void appendComment(string obj);
    string getObjectCode();
private:
    enum State
    {
       INDX = 6, RSUB = 11
    };
    int length = 3, status;
    string opcode, comment = "", operat, sym, label,object, l = "";
    string getSympIndx(string sympol);
    int hexToint(char sympol);
    char intTohex(int n);
    string format(string s);

};


#endif //UNTITLED222_INSTRUCTION_H
