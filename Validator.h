//
// Created by Lenovo on 4/19/2017.
//

#ifndef UNTITLED222_VALIDATOR_H
#define UNTITLED222_VALIDATOR_H
#include<string>
#include<vector>
#include "Command.h"
#include "CommandCreator.h"

using namespace std;

class Validator {

public:
    Validator( map<string, string> opTable, vector<vector<string> >lines, map<string, int> labels, map<int, Command*> w);
    void validateCommands();
    vector<Command*> getCommands();
    bool getFormat();
    bool Correct();

private:
    enum State
    {
        ERROR = 0, START = 1, END = 2, RESW = 3, WORD = 4, BYTE = 5, INDX = 6, LABEL = 7, ORG = 8, EQU = 9, RESB = 10,RSUB = 11,LITRX = 12, LITRC = 13, LTORG = 14
    };
    string commentinst = "", commentdir = "";
    bool inst = false, correct = true;
    vector<vector<string>> lines;
    map<string, string> opTable;
    map<int, Command*> wrong;
    map<string, int> labels;
    CommandCreator commandCreator;
    int validateInst(string s, string *l);
    int validateDirec(string d, string l, int i);
    int validateLabel(string l);
    bool checkNumber(string num);
    bool checkIndex(string l);
    bool existLabel(string l);


    bool start = false, end = false, formatfile = true;


    bool checkHexaNum(string l);
    bool checkExpression(vector<string> arr, int idx);
    bool checkDeciNum(string l);
    bool checkLiteral(string l);
    bool checkCharactersx(string basic_string);
    bool checkCharactersc(string basic_string);
    vector<string> separeteExpression(string l);
    bool forward(string lable, int idx);

    bool checkLiteralX(string l);

    bool checkLiteralC(string l);
};


#endif //UNTITLED222_VALIDATOR_H
