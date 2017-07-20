/*
 * Loader.h
 *
 *  Created on: Apr 12, 2017
 *      Author: Lenovo
 */

#ifndef LOADER_H_
#define LOADER_H_
#include<fstream>
#include<string>
#include<set>
#include <regex>
#include<vector>
#include "fileReader.h"
#include "Command.h"
#include "Validator.h"

using namespace std;

class Loader {
public:
    Loader(string fileName, map<string, string> hm);
    void readFile();
    map<string, int> getLabels();
    vector<vector <string>> getLines();
    map<int, Command*> wrong;
    map<int, Command *> getMap();

private:
    int counter = 0;
    const string directive[11] = {"START", "END", "RESW", "WORD", "BYTE", "ORG", "EQU", "RESB", "LTORG", "EQU", "ORG"};
    ifstream inFile;
    vector<Command*> *com;
    vector<string> lineVector;
    string fileName = "", line, error = "";
    bool comment();
    bool separate();
    map<string, int> labels;
    map<string, string> opMap;
    bool isDirective(string basic_string);
    bool Blank();
    vector<vector<string> > allLines;
    void validateLine(int counter, string l, string err);


};

#endif /* LOADER_H_ */
