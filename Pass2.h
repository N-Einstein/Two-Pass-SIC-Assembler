//
// Created by user on 4/22/2017.
//

#ifndef UNTITLED222_PASS2_H
#define UNTITLED222_PASS2_H


#include "Command.h"
#include "FileWriter.h"
#include "Pass1.h"

class Pass2 {
public:
    Pass2(vector<Command*> commandLists,Pass1 p1);
    void goPass2(map<string, string> sympTable, map<string, string> ltirTable);
    vector<Command*> getCommands();
private:
    enum State
    {
        LITRX = 12, LITRC = 13
    };
    vector<Command*> commandList;
    FileWriter objectWriter;
    vector<pair<int, string>> length;
    vector<string> Address;
    string totalLength, stringWR;
};


#endif //UNTITLED222_PASS2_H
