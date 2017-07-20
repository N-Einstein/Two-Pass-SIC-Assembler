//
// Created by Lenovo on 4/18/2017.
//
#include <iostream>
#include <vector>
#include <regex>
#include <map>
#include <cmath>
#include "Command.h"
using namespace std;
#include "Pass1.h"

Pass1::Pass1( vector<Command*> lines){

    l = lines;
    constructTable();
}
void Pass1::constructTable() {
    total = l.at(0)->getLength();
    int len = 0;
    int var = 1;
    Add.push_back(convertHex(total));
    for(unsigned int i = 1; i < l.size(); i++) {
      if(l.at(i)->getOperator() != "EQU")
          Add.push_back(convertHex(total));
        if (l.at(i)->getSym() != "" && l.at(i)->getSym() != "*")
            symboles[l.at(i)->getSym()] = convertHex(total);

        if (l.at(i)->getSym() == "*")
            litrals[l.at(i)->getOperator()] = convertHex(total);

        if (l.at(i)->getLabel().find("=") == 0) {
            LiteralPool.insert(l.at(i)->getLabel());
        }

        if (l.at(i)->getOperator() == "LTORG") {
            addLiterals(i);
            LiteralPool.clear();
        }else if((l.at(i)->getOperator() == "EQU")){
            int x = validateExpression(l.at(i)->getLabel());
            Add.push_back(convertHex(x));
        }
       else if(l.at(i)->getOperator() == "ORG") {
            if (l.at(i)->getLabel() == "") {
                if (lastORG == -1) {
                    l.at(i)->appendComment("No Previous ORG Command");
                } else {
                    total = lastORG;
                    lastORG = -1;
                }
            }
            else {
                total = convert(symboles[l.at(i)->getLabel()]);
              for(int j = i - 1.; j > 0; j--){
                   if(l.at(j)->getSym() == l.at(i)->getLabel()){
                       lastORG = total + l.at(j)->getLength();
                       break;
                   }
               }
            }
        }

        total += l.at(i)->getLength();

        if (l.at(i)->getStatus() != 10 && l.at(i)->getStatus() != 3){
            len += l.at(i)->getLength();
            if (len > 30) {
                length.push_back(pair<int, string>(var, convertHex(len - l.at(i)->getLength())));
                var = i;
                len = l.at(i)->getLength();
            }

        } else{
            if(len != 0) {
                length.push_back(pair<int, string>(var, convertHex(len)));
                len = 0;
            }
            if(i + 1 < l.size() && (l.at(i+1)->getStatus() != 10 && l.at(i+1)->getStatus() != 3)){
                var = i+1;
            }

            else
                var = i;
        }
    }
    if(len != 0){
        length.push_back(pair<int, string>(var, convertHex(len)));
    }

    if(LiteralPool.size() != 0){
        int end = l.size();
        addLiterals(l.size() - 1);
        for(int i = end; i < l.size(); i++) {
            litrals[l.at(i)->getOperator()] = convertHex(total);
            Add.push_back(convertHex(total));
            total += l.at(i)->getLength();
        }
    }
}

map<string, string> Pass1::getSymbols(){
    return symboles;
}

string Pass1::getTotal() {
    return convertHex(total - l.at(0)->getLength());
}

vector<string> Pass1::getAddress() {
    return Add;
}

vector< pair<int, string> > Pass1::getLegnth() {
    return length;
}

string Pass1::convertHex(int n) {
    string numHex;
    std::stringstream stream;
    stream << std::hex << n;
    stream >> numHex;
    return numHex;
}

bool Pass1::getRange() {
    return total < 32768;
}

void Pass1::addLiterals(int i) {
    int counter = 1;
    for(set<string>::iterator it = LiteralPool.begin(); it != LiteralPool.end(); it++){
        if(LiteralAll.find(*it) == LiteralAll.end()){
            Command *tmp = new Directive();
            tmp->setSym("*");
            tmp->setOperator(*it);
            tmp->setLength(getLength(*it));
            tmp->setStatus(((*it).at(1) == 'X') ? LITRX : LITRC);
            l.insert(l.begin()+ i + counter, tmp);
            counter++;
            LiteralAll.insert(*it);
            litrals[*it] = "";
        }
    }
}

int Pass1::getLength(string str) {
    return str.at(1) == 'X' ? ceil((float) (str.length() - 4) / 2) : str.length() - 4;
}
vector<Command*> Pass1::getCommands() {
    return  l;
}
map<string, string> Pass1::getLiterals() {
    return  litrals;
}

int Pass1::validateExpression(string str) {
    int ans = 0;
    int start = 0;
    vector<int> terms;
    vector<int> op;
    for(int i = 0; i < str.size(); i++){
        if(str.at(i) == '+' || str.at(i) == '-') {
            string term = str.substr(start, i - start);
            op.push_back(str.at(i) == '+' ? 1 : -1);
            if (term == "*")
                terms.push_back(total);
            else {
            string termAns = symboles[term] != "" ? symboles[term] : term;
            int result = convert(termAns);
            terms.push_back(result);
        }
            start = i+1;
        }
    }
    string term = str.substr(start,  str.size() - start );
    if (term == "*")
        terms.push_back(total);
    else {
        string termAns = symboles[term] != "" ? symboles[term] : term;
        terms.push_back(convert(termAns));
    }
    ans = terms.at(0);
       for(int i = 0; i < op.size(); i++){
           ans+= op.at(i) * terms.at(i + 1);
       }
    return  ans;
}

int Pass1::convert(string str) {
    int num;
    std::stringstream stream;
    stream << str;
    stream >> std::hex >> num;
    return num;
}
