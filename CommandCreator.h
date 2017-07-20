//
// Created by Lenovo on 5/4/2017.
//

#ifndef ASSEMBLERSIC_COMMANDCREATOR_H
#define ASSEMBLERSIC_COMMANDCREATOR_H

#include <array>
#include <vector>
#include "Command.h"

using namespace std;
class CommandCreator {
public:
    CommandCreator();
    void createCommand(vector<string> line, string err);
    void createCommand(string line, string err);
    void createCommand(int n, string l,string sym, string dirIns,string code);
    vector<Command*> getCommands();

private:
    enum State
    {
        START = 1, END = 2, RESW = 3, WORD = 4, BYTE = 5,ORG = 8, EQU = 9, RESB = 10, LTORG = 14

    };
    vector<Command*> commandList;
    bool directiveHash(int n);
    int getByteLength(string l);
    int getLength(string l);
    bool checkDeciNum(string l);
    bool checkCharactersc(string basic_string);
    string format(string s);

};


#endif //ASSEMBLERSIC_COMMANDCREATOR_H
