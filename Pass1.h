//
// Created by Lenovo on 4/18/2017.
//

#ifndef UNTITLED222_PASS1_H
#define UNTITLED222_PASS1_H


#include <string>
#include <vector>
#include<fstream>
#include<string>
#include<set>
#include <regex>
#include<vector>
#include "Command.h"
#include "Directive.h"

using namespace std;

class Pass1 {
public:
    Pass1( vector< Command*> lines);
    string getTotal();
    vector<pair<int, string>> getLegnth();
    map<string, string> getSymbols();
    vector<string> getAddress();
    vector<Command*> getCommands();
    map<string, string> getLiterals();
    bool getRange();

private:
    enum State
    {
        LITRX = 12, LITRC = 13
    };
    set<string> LiteralPool;
    set<string> LiteralAll;
    vector< Command*> l;
    map<string, string> symboles;
    map<string, string> litrals;
    vector<pair<int, string>> length;
    int total, lastORG = -1;
    void constructTable();
    string convertHex(int n);
    vector<string> Add;
    void addLiterals(int i);

    int getLength(string str);

    int validateExpression(string str);

    int convert(string basic_string);
};


#endif //UNTITLED222_PASS1_H
