//
// Created by Lenovo on 4/19/2017.
//

#include <iostream>
#include <sstream>
#include "Directive.h"
Directive::Directive(){
}

string Directive::calculate(int s, string code, string sympol) {
    if (s == RESB || s == RESW || s == LTORG || s == EQU || s == ORG)
        return "";
    else if (s == WORD)
        return validateWordSym(sympol);
    else if(s == LITRX)
        return getLitrXcode(code);
    else if(s == LITRC)
        return getLitrCcode(code);
    else
        return getCodeByte(sympol);
}

int Directive::getLength(){
    return length;
}

void Directive::setOpcode(string op){
    opcode = op;
}

void Directive::setLength(int l){
    length = l;
}
void Directive::setStatus(int s){
    status = s;
}
string Directive::getOpcode(){
    return opcode;
}
int Directive::getStatus(){
    return status;
}

void Directive::setSym(string s){
   sym = s;
}
string Directive::getSym(){
    return sym;
}
string Directive::getLine(){
    return  l;
}
string Directive::getCodeByte(string sympol){
    string cod;
    if(sympol.at(0) == 'x' || sympol.at(0) == 'X')
        return format(sympol.substr(2, sympol.size()-3));

    for(int i = 2; i < sympol.length() - 1; i++){
        int n = sympol.at(i);
        std::stringstream stream;
        stream << n;
        cod.append(stream.str());
    }
    return formatByte(cod);
}
string Directive::validateWordSym(string s){
    if(s.find("0x") != string::npos || s.find("0X") != string::npos)
        return format(s);
    int n;
    istringstream (s) >> n;
    return convertHex(n);
}
string Directive::format(string s){
    s = (s.find("0x") != string::npos || s.find("0X") != string::npos) ? s.substr(2,s.size()) : s;
    if(s.size() > 6){
        s = s.substr(s.size() - 6, s.size());
        comment = "Overflow / Underflow occures";
    }
    string ss = "";
    for(int i = 0; i < (6-s.size()); i++)
        ss.append("0");
    return ss.append(s);
}

string Directive::convertHex(int n) {
    string numHex;
    std::stringstream stream;
    stream << std::hex << n;
    stream >> numHex;
    return format(numHex);
}

string Directive::formatByte(string s) {
    string ss;
    if (s.size() < 6) {
        for (int i = 0; i < (6 - s.size()); i++)
            ss.append("0");
    }
    return ss.append(s);
}
string Directive::getLitrXcode(string s) {
    s = s.substr(3, s.size()-4);
    if(s.size() > 6){
        s = s.substr(s.size() - 6, s.size());
        comment = "Overflow / Underflow occures";
    }
    string ss = "";
    for (int i = 0; i < (6 - s.size()); i++)
            ss.append("0");
    return ss.append(s);
}
string Directive::getLitrCcode(string s) {
    s = s.substr(3, s.size()-4);
    string cod = "";
    for(int i = 0; i < s.length(); i++){
        int n = s.at(i);
        std::stringstream stream;
        stream << n;
        cod.append(stream.str());
    }
    return formatByte(cod);
}

void Directive::setLabel(string s){
    label = s;
}

string Directive::getLabel(){
    return label;
}

void Directive::setOperator(string s){
    operat = s;
}

string Directive::getOperator(){
    return operat;
}

string Directive::getComment(){
    return comment;
}

string Directive::getObjectCode(){
    return object;
}
void Directive::setObjectCode(string obj){
    object = obj;
}

void Directive::appendComment(string obj){
    comment.append(", " + obj);
}
