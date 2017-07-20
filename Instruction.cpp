//
// Created by Nada on 4/15/2017.
//

#include "Instruction.h"
#include <sstream>
#include <iostream>
using namespace std;
Instruction::Instruction() {

}
string Instruction::calculate(int s, string code, string sympol) {
    sympol = format(sympol);
    if(s == INDX) {
        sympol = getSympIndx(sympol);
    }else if(s == RSUB){
        sympol = "0000";
    }
    return code+sympol;

}
int Instruction::getLength(){
    return length;
}
void Instruction::setOpcode(string op){
    opcode = op;
}

void Instruction::setStatus(int s){
    status = s;
}
string Instruction::getOpcode(){
    return opcode;
}
int Instruction::getStatus(){
    return status;
}
void Instruction::setSym(string s){
    sym = s;
}
string Instruction::getSym(){
    return sym;
}
string Instruction::getSympIndx(string sympol){
    int dig = hexToint(sympol.at(0));
    char c = intTohex(dig+8);
    sympol.at(0) = toupper(c);
    return sympol;
}
int Instruction::hexToint(char sympol){
    int critDigit;
    std::stringstream stream;
    stream << sympol;
    stream >> std::hex >> critDigit;
    return critDigit;
}
char Instruction::intTohex(int n){
    char c;
    std::stringstream stream;
    stream << std::hex<<n;
    stream >> c;
    return c;
}
string Instruction::format(string s){
    s = s.size() > 4 ? s.substr(s.size() - 4, s.size())  : s;
    string ss;
    for(int i = 0; i < (4-s.size()); i++){
        ss.append("0");
    }
    return ss.append(s);
}
void Instruction::setLabel(string s){
    if(status == INDX){
        label = s.substr(0, s.size()-2);
    }else{
        label = s;
    }
}

string Instruction::getLabel(){
   return label;
}
void Instruction::setOperator(string s){
    operat = s;
}

string Instruction::getOperator(){
    return operat;
}

string Instruction::getComment(){
    return comment;
}

string Instruction::getObjectCode(){
    return object;
}
void Instruction::setObjectCode(string obj){
    object = obj;
}
void Instruction::appendComment(string obj){
    comment.append(", " + obj);
}

string Instruction::getLine(){
    return l;
}
