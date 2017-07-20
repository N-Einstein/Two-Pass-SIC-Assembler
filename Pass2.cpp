//
// Created by user on 4/22/2017.
//

#include <vector>
#include <map>
#include "Pass2.h"
#include "Command.h"

Pass2::Pass2(vector<Command*> commandList, Pass1 p1) {
    Pass2::commandList = commandList;
    length = p1.getLegnth();
    totalLength = p1.getTotal();
    Address = p1.getAddress();
}
void Pass2::goPass2( map<string, string> sympTable,  map<string, string> ltirTable) {
    objectWriter.writeObjectCode();
    objectWriter.writeObjectCode(commandList.at(0)->getSym(), commandList.at(0)->getLabel(),totalLength);
    for (int i = 1; i < commandList.size(); i++){
        string code = commandList.at(i)->getOpcode();
        string label = commandList.at(i)->getLabel();
        int status = commandList.at(i)->getStatus();
        string operat = commandList.at(i)->getOperator();
        if(operat == "END")
            continue;
        string sympol = sympTable.find(label) == sympTable.end() ? (ltirTable.find(label) == ltirTable.end() ? label : ltirTable[label]) : sympTable[label];
        stringWR = commandList.at(i)->calculate(status, operat.at(0) == '=' ? operat : code, sympol);
        commandList.at(i)->setObjectCode(stringWR);
        objectWriter.writeObjectCode(stringWR, i, length,Address);
    }
    objectWriter.writeObjectCode(commandList.at(0)->getLabel());
}
vector<Command*> Pass2::getCommands() {
    return  commandList;
}