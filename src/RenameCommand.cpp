//
// Created by weilern on 18/11/17.
//

#include <string>
#include "../include/Commands.h"
#include <ios>
#include <iostream>

using namespace std;

RenameCommand::RenameCommand(string args):BaseCommand(args){
}

void RenameCommand::execute(FileSystem & fs) {
    string name=rescueTheFileName(getArgs());
    vector<string> path = convertStringToVector(this->getArgs());
    BaseFile* fToRename;
    if(path[0][0] == '/' && path.size()>=1){
        path[0]=path[0].substr(1);
        fToRename = FindTheExactlyPlace(path, &fs.getRootDirectory());
    }
    else{
        fToRename = FindTheExactlyPlace(path, &fs.getWorkingDirectory());
    }
    //check if the path is not good.
    if(fToRename== nullptr){
        std::cout<<"No such file or directory" << endl;
    }
    else{
        //cant change the workingdirectory
        if(fToRename==&fs.getWorkingDirectory())
            std::cout<<"Can't rename the working directory" << endl;
        else{
            //check if the child already exsit.
            path.erase(path.end());
            BaseFile* fParent=FindTheExactlyPlace(path,&fs.getRootDirectory());
            //i do direct casting to directory bec
            // ause is in middle of path.
            if(findTheChild(dynamic_cast<Directory*>(fParent),name)!= nullptr)
                ;
            else
                fToRename->setName(name);
        }
    }
    setArgs(getArgs()+" "+name);
}

string RenameCommand::toString(){
    string output=getArgs();
    switchSpaceToLine(&output);
    return "rename "+output;
}
string RenameCommand::rescueTheFileName(string args)
{
    bool  flag=true;
    string output="";
    for(size_t i=0; i<getArgs().size() && flag; i++){
        //saperate the string for source and destination
        if (getArgs()[i]=='_'){
            output=getArgs().substr(i+1);
            setArgs(getArgs().substr(0,i));
            flag=false;
        }
    }
    return output;
}
