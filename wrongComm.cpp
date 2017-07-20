//
// Created by Lenovo on 5/3/2017.
//

#include "wrongComm.h"

wrongComm::wrongComm(string line, string error){
    l = line;
    comment = error;
}
string wrongComm::getComment(){
    return comment;
}

string wrongComm::getLine(){
    return l;
}

int wrongComm::getLength(){ return 0;}
void wrongComm::setOpcode(string op){}
void wrongComm::setLength(int l){}
void wrongComm::setStatus(int s){}
string wrongComm::getOpcode(){ return "";}
int wrongComm::getStatus(){return 404;}
void wrongComm::setSym(string basic_string) {}
string wrongComm::getSym() {return "";}
void wrongComm::setLabel(string s){}
string wrongComm::getLabel(){return "";}
void wrongComm::setOperator(string s){}
string wrongComm::getOperator(){return "";}
string wrongComm::calculate(int s, string code, string sympol){
    return "";
}
void wrongComm::appendComment(string obj){
    comment.append(", " + obj);
}
