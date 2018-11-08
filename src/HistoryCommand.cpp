
#include <string>
#include <vector>
#include <iostream>
#include "../include/Commands.h"
using namespace std;

//const vector<BaseCommand *> & history;

//constructor
HistoryCommand::HistoryCommand(string args, const vector<BaseCommand *> & history):BaseCommand(args),history(history){};


void HistoryCommand::execute(FileSystem & fs){
    for (size_t i=0; i<this->history.size();i++)
        std::cout <<i<< '\t'<<history[i]->toString() <<'\n';
}

string HistoryCommand::toString(){
    return "history "+getArgs();
}

