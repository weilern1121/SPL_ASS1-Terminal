//
// Created by weilern on 18/11/17.
//

#include <string>
#include "../include/Commands.h"
#include <iostream>
using namespace std;

ErrorCommand::ErrorCommand(string args): BaseCommand(args){
}

void ErrorCommand::execute(FileSystem & fs){

    std::cout << getArgs().substr(0,getArgs().find(" "))<<": Unknown command"<< endl;
}
string ErrorCommand::toString(){
    return getArgs();
}
