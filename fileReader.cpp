//
// Created by user on 4/13/2017.
//

#include "fileReader.h"
#include <string>
#include <map>
#include<fstream>
#include <iostream>

using namespace std;

fileReader::fileReader(string file) {
    name = file;
}
bool fileReader::readTable() {
    table.open(name);
    if (!table.is_open())
        return false;

    while (table >> key >> value)
        opTable.insert(pair<string, string>(key, value));

    return true;
}

map <string, string> fileReader::getMap(){
    return opTable;
};
