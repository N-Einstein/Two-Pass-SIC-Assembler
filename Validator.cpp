//
// Created by Lenovo on 4/19/2017.
//

#include <map>
#include <set>
#include "Validator.h"
#include "Directive.h"
#include "Instruction.h"
#include "wrongComm.h"
#include <sstream>
#include <regex>
#include <iostream>
using namespace std;


Validator::Validator( map<string, string> opTable, vector<vector<string> >lines, map<string, int> labels, map<int, Command*> w){
    Validator::opTable = opTable;
    Validator::labels = labels;
    Validator::wrong = w;
    Validator::lines = lines;
}

void Validator::validateCommands() {
    int s, d;
     if(lines.at(0).size() == 2 && lines.at(0).at(1) == "START")
        lines.at(0).push_back("0000");
    for (int i = 0; i < lines.size(); i++){
        commentinst = commentdir = "";
        if(lines.at(i).size() != 0) {
            inst = false;
            string sym = (lines.at(i).size() == 3) ? lines.at(i).at(0) : "";
            string inst_dirc = (lines.at(i).size() == 2 || lines.at(i).size() == 1) ? lines.at(i).at(0) : lines.at(i).at(1);
            string label = (lines.at(i).size() == 1) ? "" : ((lines.at(i).size() == 2) ? lines.at(i).at(1) : lines.at(i).at(2));
            s = validateInst(inst_dirc, &label);
            if(!s) {
                d = validateDirec(inst_dirc, label, i);
                if(!d) {
                    commandCreator.createCommand(lines.at(i), inst ? commentinst : commentdir);
                    correct = false;
                }
                else
                    commandCreator.createCommand(d, label, sym, inst_dirc,opTable[inst_dirc]);
            }
            else
                commandCreator.createCommand(s, label,sym, inst_dirc,opTable[inst_dirc]);
        }else{
            commandCreator.createCommand(wrong[i]->getLine(), wrong[i]->getComment());
            correct = false;
        }
}
    if(!(start && end)){
        formatfile = false;
    }
}
int Validator::validateInst(string s,string *l){
   if(opTable[s] != "") {
       inst = true;
       if(s == "RSUB" && l->size() == 0)
           return RSUB;
       if(checkLiteralX(*l)){
           *l = "=X" + l->substr(2, l->size()-2);
           return LITRX;
       }
       if(checkLiteralC(*l)){
           *l = "=C" + l->substr(2, l->size()-2);
           return LITRC;
       }
       return validateLabel(*l);
   }
    commentinst.append("  Invalid instruction! ");
    return ERROR;
}
int Validator::validateDirec(string d, string l, int idx){
    if(d == "START"){
        if(!start)
            start = true;
        else{
            commentdir.append("  Multiple Starts!!!!  ");
            return ERROR;
        }
     if(checkNumber(l)){
         return START;
     }
    }else if(d == "END") {
        if (!end)
            end = true;
        else{
            commentdir.append("  Multiple ENDs!!!!  ");
            return ERROR;
        }
        if (existLabel(l)) {
                return END;
        }
    }else if(d == "WORD"){
        if(checkNumber(l)){
            return WORD;
        }
    }else if(d == "BYTE"){
        if(checkCharactersx(l) || checkCharactersc(l)){
            return BYTE;
        } else {
            commentdir.append(" invalid character ");
        }
    }else if(d == "RESW"){
        if(checkNumber(l)){
            return RESW;
        }
    }else if(d == "RESB") {
        if (checkNumber(l)) {
            return RESB;
        }
    }
    else if(d == "ORG"){
        if(l =="" || (existLabel(l) && !forward(l, idx)))
            return ORG;
        commentdir.append("Invalid Org usage!");
    }else if(d == "EQU"){
       if( checkExpression(separeteExpression(l), idx) || l == "*") {
           return EQU;
       }
        else{
           commentdir.append(" invalid Expression ");
       }
    } else if(d == "LTORG"){
        return LTORG;
    }
    else commentdir.append("  Invalid Directive! ");
    return ERROR;
}
int Validator::validateLabel(string l){
   if(l.find(',') != string::npos){
       if(checkIndex(l))
           return INDX;
   }else {
       if(existLabel(l))
           return LABEL;
   }
    commentinst = "invalid label";
    return ERROR;
}
bool Validator::checkNumber(string num) {
    regex numeric("^(0(X|x)[0-9A-E]+|\\d)\\d*$");
    if(regex_match(num, numeric))
          return true;
    else{
        commentinst.append(" invalid number ");
        return false;
    }
}

bool Validator::checkCharactersx(string s) {
    regex hex("^(X|x)'[0-9A-F]+'$");
    return regex_match(s, hex);
}

bool Validator::checkCharactersc(string s) {
    regex str("^(C|c)'[0-9A-Za-z]+'$");
    return regex_match(s, str);
}

bool Validator::checkIndex(string l){
    stringstream ss(l);
    string substr;
    getline( ss, substr, ',' );
    if(existLabel(substr)){
        if((l.find_first_of(',') == l.size() - 2) && l.at(l.size()-1) == 'X')
                return true;
    }
    commentinst = " Wrong Syntax ";
    return false;
}

bool Validator::existLabel(string l){
    transform(l.begin(), l.end(), l.begin(), ::toupper);
    return labels.find(l) != labels.end();
}

vector<Command*> Validator::getCommands() {
    return  commandCreator.getCommands();
}

bool Validator::checkHexaNum(string l) {
    regex hex("^0(X|x)[0-9A-E]+$");
    return regex_match(l, hex);
}

bool Validator::checkDeciNum(string l) {
    regex deci("^[0-9]+$");
    return regex_match(l, deci);
}

bool Validator::checkLiteral(string l) {

    return checkLiteralX(l) || checkLiteralC(l);
}

bool Validator::checkLiteralX(string l) {
    regex n("^=(X|x)'[0-9A-Fa-f]+'$");
    return regex_match(l, n);
}

bool Validator::checkLiteralC(string l) {
    regex c("^=(C|c)'[0-9A-Za-z]+'$");
    return regex_match(l, c);
}

vector<string>  Validator::separeteExpression(string l){
    vector<string> arr;
    vector<string> arr2;
    std::stringstream line(l);
    string w;
    while(getline(line, w, '-')){
        arr.push_back(w);
    }
    for(vector<string>::iterator iterator = arr.begin(); iterator != arr.end(); iterator++){
        std::stringstream s(*iterator);
        while(getline(s, w, '+')){
            arr2.push_back(w);
        }
    }
    return arr2;
}
bool  Validator::checkExpression(vector<string> arr, int idx){

    for(vector<string>::iterator iterator = arr.begin(); iterator != arr.end(); iterator++){
        if((!existLabel(*iterator) || forward(*iterator, idx)) && !checkDeciNum(*iterator) && *iterator != "*") {
            return false;
        }
    }
    return true;
}

bool  Validator::forward(string lable, int idx){
    return labels[lable] > idx;
}

bool Validator::getFormat() {
    return formatfile;
}

bool Validator::Correct() {
    return correct;
}