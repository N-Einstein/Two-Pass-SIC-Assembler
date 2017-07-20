//
// Created by NADA on 4/15/2017.
//

#include "FileWriter.h"
#include "Command.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

FileWriter::FileWriter() {
    LitFile.open("LITAB.txt");
}
void FileWriter::writeObjectCode(){
    myfile.open("objectCode.txt");
}
void FileWriter::writeObjectCode(string num, string s, string len){
    for(int i = num.size(); i < 6; i++)
        num.append(" ");
    myfile << "H^" + num + "^" + s + "^" + len;
}
void FileWriter::writeObjectCode(string s, int count, vector<pair<int, string>> len,vector<string> address){
    static unsigned int counter = 0;
    if((counter) < len.size() && (count) == len.at(counter).first) {
        myfile << "\nT^" + address.at(count) + "^" + len.at(counter).second +"^"+s;
        counter++;
    }
    else
        myfile<< ((s == "")? s : ("^" + s));

}
void FileWriter::writeObjectCode(string s){
    myfile<< "\nE^" + s;

}

void FileWriter::writeSymbole(map<string, string> symboles) {
    myfile.open("symboleTable.txt");
    for(it_sym iterator = symboles.begin(); iterator != symboles.end(); iterator++){
        string str = iterator->first;
        while(str.size() < 8) str += " ";
        myfile << str +  "\t" << iterator->second << endl;
    }
    myfile.close();
}

void FileWriter::writeinter(vector<Command *> com, bool ok, bool inRange) {
    myfile.open("inter.txt");
    for(int i = 0; i < com.size(); i++){
        if(com.at(i)->getComment() == "") {
            putLine(com.at(i));
            myfile << com[i]->getComment();
            myfile << endl;
        }
        else{
            if(com[i]->getLine().length() == 0)
                myfile<< com[i]->getOperator()<< "\t" << com[i]->getComment()<<endl;
            else
                myfile << com[i]->getLine()<< "\t" << com[i]->getComment()<<endl;
        }
    }
    if(!ok) myfile << "Missing Start or End or BOTH!!!!!"<<endl;
    if(!inRange) myfile << "Program Exceeded SIC Memory, Permission denied!!!!"<<endl;
    myfile.close();
}

void FileWriter::writeListing(vector<Command *> com, vector<string> add) {
    myfile.open("listing.txt");
    for(int i = 0; i < com.size(); i++){
        if(com.at(i)->getSym() == "*")
            writeLITAB(com.at(i), add.at(i));
        myfile << add.at(i) << "\t";
        putLine(com.at(i));
        myfile << com[i]->getObjectCode();
        myfile <<endl;
    }
    myfile.close();
    LitFile.close();
}
void FileWriter::writeLITAB(Command *com, string add) {
    LitFile << com->getOperator() << "\t"<< com->getOperator().substr(3, com->getOperator().size() - 4)<< "\t";
    LitFile << com->getLength()<<"\t"<< add<<endl;
}
void FileWriter::putLine(Command *cm) {

    string crnt =  cm->getSym();
    while (crnt.length() < 8) crnt += ' ';
    myfile << crnt << "\t";

    crnt =  cm->getOperator();
    while (crnt.length() < 5) crnt += ' ';
    myfile << crnt << "\t";


    crnt =  cm->getLabel();
    if (cm->getStatus() == 6)
        crnt.append(",X");
    while (crnt.length() < 18) crnt += ' ';
    myfile << crnt << "\t";
}

string FileWriter::convertHex(int n) {
    string numHex;
    stringstream stream;
    stream << std::hex << n;
    stream >> numHex;
    return numHex;
}

string FileWriter::format(string s){
    s = s.size() > 4 ? s.substr(s.size() - 4, s.size())  : s;
    string ss;
    for(int i = 0; i < (4-s.size()); i++){
        ss.append("0");
    }
    return ss.append(s);
}