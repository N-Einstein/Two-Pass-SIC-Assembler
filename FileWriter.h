//
// Created by user on 4/15/2017.
//

#ifndef UNTITLED_OBJECTWRITER_H
#define UNTITLED_OBJECTWRITER_H
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include "Command.h"

using namespace std;
typedef map<string, string> ::iterator it_sym;

class FileWriter {
public:
    FileWriter();
    void writeObjectCode(string nam, string s, string len);
    void writeinter(vector< Command*> com, bool ok, bool inRange);
    void writeObjectCode(string s, int count,vector<pair<int, string>> len,vector<string> address);
    void writeObjectCode(string s);
    void writeListing(vector<Command *> com, vector<string> add);
    void writeSymbole(map<string, string> symboles);
    void  writeObjectCode();

private:
    ofstream myfile, LitFile;
    void putLine(Command *cm);
    string convertHex(int n);
    string format(string s);
    void writeLITAB(Command *com, string add);
};


#endif //UNTITLED_OBJECTWRITER_H
