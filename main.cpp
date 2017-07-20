//============================================================================
// Name        : Assembler.cpp
// Author      : NA
// Version     :
// Copyright   : Your copyright notice
// Description : Assembler in C++, Ansi-style
//============================================================================
#include <iostream>
#include<fstream>
#include <iomanip>
#include "Loader.h"
#include "fileReader.h"
#include "Command.h"
#include "Pass1.h"
#include "Validator.h"
#include "FileWriter.h"
#include "Pass2.h"

using namespace std;

ifstream inFile;
ofstream outFile;

int main() {
    fileReader readOp("optable.txt");
    readOp.readTable();
    Loader fileLoader("tst.asm", readOp.getMap());
    fileLoader.readFile();
    Validator v(readOp.getMap(),fileLoader.getLines(), fileLoader.getLabels(), fileLoader.getMap());
    v.validateCommands();

    Pass1 p1(v.getCommands());
    FileWriter  fw;
    fw.writeinter(v.getCommands(), v.getFormat(), p1.getRange());
    fw.writeSymbole(p1.getSymbols());
    if(p1.getRange() && v.Correct()) {
        Pass2 p2(p1.getCommands(), p1);
        p2.goPass2(p1.getSymbols(), p1.getLiterals());
       fw.writeListing(p1.getCommands(), p1.getAddress());
    } else
        cout << "Can't continue to Pass two !!!\nFix the errors in intermediate file!!!"<<endl;

    return 0;

}
