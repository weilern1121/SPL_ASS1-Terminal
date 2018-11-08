//
// Created by weilern on 14/11/17.
//

    #include <string>
    #include <vector>
#include <iostream>
#include "../include/Commands.h"
    using namespace std;

    //constructor
    PwdCommand::PwdCommand(const string args):BaseCommand(args){
    }

// Every derived class should implement this function according to the document (pdf)
    void PwdCommand::execute(FileSystem & fs){
    std:: cout <<(fs.getWorkingDirectory().getAbsolutePath())<<endl;
    //std:: cout <<this->toString();

}
string PwdCommand::toString(){
        return "pwd "+getArgs();
    }

