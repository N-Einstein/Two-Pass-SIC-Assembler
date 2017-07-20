//
// Created by Lenovo on 4/19/2017.
//

#ifndef UNTITLED222_DIRECTIVE_H
#define UNTITLED222_DIRECTIVE_H
#include"command.h"

class Directive : public Command{
public:
     Directive();
     string calculate(int s, string code, string sympol);
     int getLength();
     void setStatus(int s);
     void setLength(int l);
     void setOpcode(string op);
     int getStatus();
     string getOpcode();
     void setSym(string s);
     string getSym();
     void setLabel(string s);
     string getLabel();
    void setOperator(string s);
    string getOperator();
    string getComment();
    void setObjectCode(string obj);
    string getObjectCode();
    void appendComment(string obj);
    string getLine();
private:
    enum State
    {
        RESW = 3, WORD = 4, BYTE = 5, RESB = 10, LITRX = 12, LITRC = 13, LTORG = 14, EQU = 9, ORG = 8
    };
    int length = 0, status;
    string opcode, comment="", sym, label,operat,object, l = "";
    string getCodeByte(string sympol);
    string validateWordSym(string s);
    string format(string s);
    string convertHex(int n);
    string formatByte(string s);

    string getLitrXcode(string s);

    string getLitrCcode(string s);
};


#endif //UNTITLED222_DIRECTIVE_H
