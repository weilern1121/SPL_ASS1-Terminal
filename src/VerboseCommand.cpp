#include <string>
#include <vector>
#include <iostream>
#include "../include/Commands.h"
#include "../include/GlobalVariables.h"
using namespace std;

VerboseCommand::VerboseCommand(string args):BaseCommand(args){
}

void VerboseCommand::execute(FileSystem & fs){

    vector<string> path=convertStringToVector(this->getArgs());
    if(path.size()!=1 ||path[0].size()!=1||!isdigit(path[0][0]))
        std::cout<<"Wrong verbose input" << endl;
    int i=atoi(path[0].c_str());
    if(i!=1 && i!=2 && i!=3 && i!=0)
        std::cout<<"Wrong verbose input" << endl;
    else{
        verbose=i;
    }

}

string VerboseCommand::toString(){
    return "verbose "+getArgs();
}