//
// Created by weilern on 18/11/17.
//

#include <string>
#include "../include/Commands.h"
#include <iostream>
using namespace std;

//Constructor
CdCommand::CdCommand(string args):BaseCommand(args){
}

void CdCommand::execute(FileSystem & fs){
    Directory* initialWD= (&fs.getWorkingDirectory());
    bool isCut=false;
    //first- check if there is a need to go from the root
    if(this->getArgs().size()>0 && this->getArgs().at(0)=='/') {
        fs.setWorkingDirectory(&fs.getRootDirectory());
        setArgs(getArgs().substr(1));
        isCut=true;
    }
    //convert the input args to vector
    vector<string> path=convertStringToVector(this->getArgs());
    bool exists=true;
    //save a pointer to the initial workingDirectory- because if there is ilegal argument-nothing gonna change
    while(path.size()>0 && exists){

        //if the path is in mid but the dir dont have more children
        if(fs.getWorkingDirectory().getChildren().size()==0 && path[0]!="..")
            exists=false;
        BaseFile* tmp=findTheChild(&fs.getWorkingDirectory() , path[0]);
           if(tmp!= nullptr){
                //i found the path than check if its dir or file
                //if its file close the function and print messege
                if(!(tmp->instanceOf())){
                    cout<<"Not a directory" << endl;
                    exists = false;
                }
                else {
                    //if its dir change the rootdir, remove the dir from vector and return to while
                    fs.setWorkingDirectory(dynamic_cast<Directory*>(tmp));
                    path.erase(path.begin());
                }
            }
               //else- the function didn't find the location-there is not directory
           else {
               exists = false;
               std::cout << "The system cannot find the path specified" << endl;
               fs.setWorkingDirectory(initialWD);
           }
        tmp= nullptr;
        }
    if(isCut)
        setArgs("/"+getArgs());
    path.clear();
    initialWD= nullptr;
}

//toSring
string CdCommand::toString(){
    return "cd "+getArgs();
}







