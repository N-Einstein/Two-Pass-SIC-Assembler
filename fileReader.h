//
// Created by user on 4/13/2017.
//

#ifndef UNTITLED_FILEREADER_H
#define UNTITLED_FILEREADER_H

#include <string>
#include <fstream>
#include <map>
using namespace std;

class fileReader {
public:
    fileReader(string file);
    bool readTable();
    map <string, string> getMap();
private:
    ifstream table;
    string key, value, name;
    map <string, string> opTable;
};


#endif //UNTITLED_FILEREADER_H