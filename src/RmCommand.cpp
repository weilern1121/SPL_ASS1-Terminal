//
// Created by weilern on 18/11/17.
//

#include <string>
#include "../include/Commands.h"
#include <iostream>
using namespace std;

RmCommand::RmCommand(string args):BaseCommand(args){
}

void RmCommand::execute(FileSystem & fs){
    //first- check if there is a need to go from the root
    Directory* initialWD= (&fs.getWorkingDirectory());
    bool isCut=false;
    if(this->getArgs().size()>0 && this->getArgs().at(0)=='/') {
        fs.setWorkingDirectory(&fs.getRootDirectory());
        setArgs(getArgs().substr(1));
        isCut=true;
    }
    vector<string> path = convertStringToVector(this->getArgs());
    //don't allow the to remove rootdirectory
    if(path.size()==0)
        std::cout<<"Can't remove directory" << endl;
    else {
        string ToRemoveStr = path[path.size() - 1];
        path.erase(path.end());
        BaseFile *fToRemove;
        Directory *fParntRemove = ((Directory *) FindTheExactlyPlace(path, &fs.getWorkingDirectory()));
        if(fParntRemove == nullptr){
            fToRemove = findTheChild(&fs.getWorkingDirectory(), ToRemoveStr);
        } else
            fToRemove = findTheChild(fParntRemove, ToRemoveStr);

            if (fToRemove == nullptr) {
                std::cout << "No such file or directory" << endl;
                fs.setWorkingDirectory(initialWD);
            } else {
                if(!(legalPathWorkingDirectory(*(dynamic_cast<Directory*>(fToRemove)), initialWD, fs.getRootDirectory()))
                        || &fs.getWorkingDirectory()==fToRemove) {
                    std::cout << "Can't remove directory" << endl;
                    fs.setWorkingDirectory(initialWD);
                }
                    else {

                            fParntRemove->removeFile(fToRemove);
                            delete fToRemove;


                }
            }
        fParntRemove = nullptr;
        }
    if(isCut)
        setArgs("/"+getArgs());
    path.clear();
    initialWD= nullptr;
}


string RmCommand::toString(){
    return "rm "+getArgs();
}

void RmCommand::recursivelyRemove(Directory* rootToRemove){
    for(size_t i=0; i<rootToRemove->getChildren().size();i++){
        if(dynamic_cast<Directory*>(rootToRemove->getChildren()[i])) {
            recursivelyRemove(dynamic_cast<Directory *>(rootToRemove->getChildren()[i]));
        }
    }
    for(size_t i=rootToRemove->getChildren().size()-1; i>0;i--){
        //we assume it will remove the object and the pointer.
        rootToRemove->removeChildren(i,true);
        //rootToRemove->getChildren().erase(rootToRemove->getChildren().end()-i);
    }
    delete(rootToRemove);
}

