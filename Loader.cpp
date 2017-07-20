/*
 * Loader.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: Nada
 */
#include <iostream>
#include<fstream>
#include <sstream>
#include <vector>
#include <regex>
#include "Loader.h"
#include "Command.h"
#include "Directive.h"
#include "wrongComm.h"

using namespace std;

regex valid3("\\s*\\w+\\s+\\w+\\s+.+\\s*");
regex valid2("\\s*\\w+\\s+.+\\s*");
regex valid1("\\s*\\w+\\s*");

Loader::Loader(string fileName, map<string, string> hm) {
    Loader::fileName = fileName;
    opMap = hm;
}

void Loader::readFile() {
    inFile.open(fileName);
    if (!inFile.is_open()) {
        cout << "File Doesn't Exist!" << endl;
        return;
    }
    while (inFile.good()) {
        error = "";
        lineVector.clear();
        getline(inFile, line);
        if (Blank() || comment())
            continue;

        if (regex_match(line, valid2) || regex_match(line, valid3) || regex_match(line, valid1)) {
            if(!separate()){
               validateLine(counter, line, error);
                vector<string> x;
                allLines.push_back(x);}
        }
        else{
            validateLine(counter, line, "Wrong Command Format");
            vector<string> x;
                allLines.push_back(x);}

        counter++;
    }
}

bool Loader::separate() {
    stringstream ssin(line);
    string tmp;
    int i = 0;
    if (regex_match(line, valid3)) {
        while (i++ < 3) {
            ssin >> tmp;
            if (i == 1) {
                transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
                if (labels.find(tmp) != labels.end())
                    error += "Repeated Label: " + tmp;
                if(opMap.find(tmp) != opMap.end() || isDirective(tmp)){
                    error += ", Invalid Label Name --> it is an instruction or directive: " + tmp;
                }
                if(tmp.size() > 8)
                        error += ", Too Long Label Name > 8 Characters: " + tmp;
                if(error == "") {
                    labels[tmp] =  counter;
                }

            } else if(i == 2)
                transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
            else if(i== 3 && tmp.size() > 18)
                error +=  ", Too Long Label operand > 18 Characters: " + tmp;
            lineVector.push_back(tmp);
        }
        while (i++ < 2) {
            ssin >> tmp;
            lineVector.push_back(tmp);
        }
    } else if (regex_match(line, valid2)) {
        while (i++ < 2) {
            ssin >> tmp;
            if(i == 1)
                transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
            lineVector.push_back(tmp);
        }
    } else {
        ssin >> tmp;
        transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
        lineVector.push_back(tmp);
    }
    if(error == ""){
        allLines.push_back(lineVector);
        return true;
    }
    return false;
}
bool Loader::comment() {
    regex Comment("^\\s*\\..*");
    return regex_match(line, Comment);
}
map<string, int> Loader::getLabels(){
  return labels;
}

vector<vector<string>> Loader::getLines() {
    return allLines;
}

bool Loader::isDirective(string str) {
   return find(begin(directive), end(directive), str) != end(directive);
}

bool Loader::Blank() {
    regex blank("\\s*");
    return regex_match(line, blank);
}

void Loader::validateLine(int idx, string l, string err){
    Command *cm = new wrongComm(l, err);
    wrong[idx] = cm;
}

map<int, Command*> Loader::getMap(){
    return wrong;
}
