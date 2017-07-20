//
// Created by Lenovo on 5/4/2017.
//

#include <sstream>
#include <regex>
#include <cmath>
#include "CommandCreator.h"
#include "wrongComm.h"
#include "Directive.h"
#include "Instruction.h"

CommandCreator::CommandCreator(){

}
void CommandCreator::createCommand(vector<string> line, string err){
    string l = "";
    string tmp;
    for(int i = 0; i < line.size(); i++){
        if(i == 0){
            if(tmp.size() < 8)
                tmp+=" ";
        }
        else if(i == 1){
            if(tmp.size() < 6)
                tmp+=" ";
        }
        l.append(line.at(i)).append("\t");
    }
    Command *cm = new wrongComm(l, err);
    commandList.push_back(cm);

}
void CommandCreator::createCommand(string line, string err){
    Command *cm = new wrongComm(line, err);
    commandList.push_back(cm);

}

void CommandCreator::createCommand(int n, string l,string sym, string dirIns, string code){
    if(directiveHash(n)){
        Command *dir = new Directive;
        dir->setStatus(n);
        dir->setOpcode("NULL");
        dir->setLabel( (n==START) ? format(l) : l);
        dir->setOperator(dirIns);
        switch(n){
            case START:
                dir->setLength(getLength((l.find("0x")!= string::npos  || l.find("0X")!= string::npos )? l : "0X"+l)); break;
            case RESW:
                dir->setLength(getLength(l) * 3); break;
            case RESB:
                dir->setLength(getLength(l)); break;
            case WORD:
                dir->setLength(3); break;
            case END:
                dir->setLength(0); break;
            case BYTE:
                dir->setLength(getByteLength(l)); break;
            case ORG: break;
            case EQU: break;
            default: break;
        }
        dir-> setSym(sym);
        commandList.push_back(dir);
    }else{
        Command *inst = new Instruction;
        inst->setStatus(n);
        inst->setOpcode(code);
        inst->setSym(sym);
        inst->setLabel(l);
        inst->setOperator(dirIns);
        commandList.push_back(inst);
    }
}
bool CommandCreator::directiveHash(int n){
    return n == START || n == WORD || n == BYTE || n == RESW || n== RESB || n == END || n == ORG || n == EQU || n == LTORG;
}
int CommandCreator::getByteLength(string l){

    return (checkCharactersc(l))? l.length() - 3 : ceil((l.length() - 3) / 2);
}

int CommandCreator::getLength(string l) {
    int num;
    if (checkDeciNum(l))
        istringstream (l) >> num;
    else {
        std::stringstream stream;
        stream << l;
        stream >> std::hex >> num;
    }
    return num;
}

bool CommandCreator::checkDeciNum(string l) {
    regex deci("^[0-9]+$");
    return regex_match(l, deci);
}
bool CommandCreator::checkCharactersc(string s) {
    regex str("^(C|c)'[0-9A-Za-z]+'$");
    return regex_match(s, str);
}
vector<Command*> CommandCreator::getCommands() {
    return  commandList;
}


string CommandCreator::format(string s){
    s = (s.find("0x") != string::npos || s.find("0X") != string::npos) ? s.substr(2,s.size()) : s;
    s = s.size() > 6 ? s.substr(s.size() - 6, s.size()): s;
    string ss;
    for(int i = 0; i < (6-s.size()); i++)
        ss.append("0");
    return ss.append(s);
}
