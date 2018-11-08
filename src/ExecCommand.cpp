//
// Created by weilern on 17/11/17.
//

#include <string>
#include <vector>
#include <iostream>
#include "../include/Commands.h"
using namespace std;

// const vector<BaseCommand *> & history;

//constructor
ExecCommand::ExecCommand(string args, const vector<BaseCommand *> & history):BaseCommand(args),history(history){};

void ExecCommand::execute(FileSystem & fs){

    bool checkInput=true;
    for (size_t i=0; i<getArgs().size() && checkInput;i++){
        if((getArgs().at(i))>'9' || (getArgs().at(i))<'0')
            checkInput=false;
    }
    if(!checkInput)
        cout<<"Command not found" << endl;
    else{
        size_t index=stoi(getArgs());
        if (index>history.size())
            cout<<"Command not found" << endl;
        else{
            (this->history[index])->execute(fs);
            //maybe needed to add the command to history
        }
    }
}

vector<BaseCommand *> ExecCommand::getHistory(){
    return this->history;
}

string ExecCommand::toString(){
    return "exec "+getArgs();
}
