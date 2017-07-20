//
// Created by Lenovo on 4/18/2017.
//

#ifndef UNTITLED222_COMMAND_H
#define UNTITLED222_COMMAND_H
#include<string>

using namespace std;

class Command {
public:
    Command();
    virtual string calculate(int s, string code, string sympol);
    virtual int getLength();
    virtual void setStatus(int s);
    virtual void setLength(int l);
    virtual void setOpcode(string op);
    virtual string getSym();
    virtual int getStatus();
    virtual string getOpcode();
    virtual void setSym(string s);
    virtual void setLabel(string s);
    virtual string getLabel();
    virtual void setOperator(string s);
    virtual string getOperator();
    virtual string getComment();
    virtual string getLine();
    virtual string getObjectCode();
    virtual void setObjectCode(string obj);
    virtual void appendComment(string obj);
};


#endif //UNTITLED222_COMMAND_H
