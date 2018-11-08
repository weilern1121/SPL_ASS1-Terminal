
#include <string>
#include "../include/Commands.h"
#include <iostream>
using namespace std;

MkdirCommand::MkdirCommand(string args):BaseCommand(args){
}

void MkdirCommand::execute(FileSystem & fs){
    bool isCut=false;
    if(getArgs()=="")
        std::cout<<"The system cannot find the path specified" << endl;
    else {
        string output;
        if (getArgs().at(0) == '/') {
            setArgs(getArgs().substr(1));
            output=goToTrip(&fs.getRootDirectory());
            isCut=true;
        }
        else {
            output=goToTrip(&fs.getWorkingDirectory());
        }
        if(output.compare("")!=0)
            std::cout << output<<endl;
    }
    if(isCut){
        setArgs("/"+getArgs());
    }
}

string MkdirCommand::toString(){
    return "mkdir "+getArgs();
}

string MkdirCommand::goToTrip(Directory* dir){
    //covert the input args to vector
    vector<string> path=convertStringToVector(this->getArgs());
    bool thePathNotAlreadyExsist=false;
    BaseFile* tmp;
    while(path.size()>0){
        //mybe change to reference
        tmp=findTheChild(dir,path[0]);
        if(tmp== nullptr){
            Directory* newDir=new Directory(path[0],dir);
            (*dir).addFile(newDir);
            dir=newDir;
            //delete newDir;
            path.erase(path.begin());
            if(path.size()==0)
                thePathNotAlreadyExsist=true;
            newDir= nullptr;
        }
        else{
            if(dynamic_cast<File*>(tmp))
                return "The directory already exists" ;
            else{
                //not sure on the next casting
                dir=dynamic_cast<Directory*>(tmp);
                path.erase(path.begin());
                //delete tmp;
                tmp= nullptr;
            }
        }
    }
    vector<string>::iterator it = path.begin();
    while (it != path.end()) {
        delete (&it);
        it = path.erase(it);
    }
    if(!thePathNotAlreadyExsist)
        return "The directory already exists";
    else
        return "";

}