//
// Created by weilern on 18/11/17.
//

#include <string>
#include "../include/Commands.h"
#include <ios>
#include <iostream>

using namespace std;

MkfileCommand::MkfileCommand(string args):BaseCommand(args){
}
void MkfileCommand:: execute(FileSystem & fs){
    //need add input check
    //covert the file's size  from string to int.
    int size=cutTheSize();
    //i add this sitution- the command don't get size
    if(size==-1)
        cout<<"Unknown command"<<endl;
    else {
        vector<string> path = convertStringToVector(this->getArgs());
        string FileName = path[path.size() - 1];
        path.erase(path.end());
        //real not sure for the next line.
        Directory *dir;
        bool isCut=false;
        if (getArgs().at(0) == '/') {
            setArgs(getArgs().substr(1));
            isCut=true;
            dir = dynamic_cast<Directory *>( FindTheExactlyPlace(path, &fs.getRootDirectory()));
        } else
            dir = dynamic_cast<Directory *>(FindTheExactlyPlace(path, &fs.getWorkingDirectory()));
        if (dir == nullptr) {
            std::cout << "The system cannot find the path specified" << endl;
        } else {
            if (findTheChild(dir, FileName) == nullptr) {
                dir->addFile(new File(FileName, size));
            }
            else {
                std::cout << "File already exists" << endl;

            }
        }
        setArgs(getArgs()+" "+std::to_string(size));
        if(isCut){
            setArgs("/"+getArgs());
        }
        //delete
        path.clear();
        dir = nullptr;
    }
}

string MkfileCommand::toString(){
    string output=getArgs();
    switchSpaceToLine(&output);
    return "mkfile "+output;
}

//covert the file's size  from string to int.
int MkfileCommand:: cutTheSize() {
//mybe need to remove from args the spaces
    size_t i=0;
    bool sizeIsExsit=false;
    string size;
    while(i<getArgs().size() && !sizeIsExsit) {
        if ((getArgs().at(getArgs().size() - 1 - i)) >= '0' && (getArgs().at(getArgs().size() - 1 - i)) <='9')
        i++;
        else {
            if (i == 0 || ((getArgs().at(getArgs().size() - 1 - i))>='A' && (getArgs().at(getArgs().size() - 1 - i)) <='Z')
                 || ((getArgs().at(getArgs().size() - 1 - i))>='a' && (getArgs().at(getArgs().size() - 1 - i)) <='z'  ))
                return -1;
            else {
                size = getArgs().substr(getArgs().size() - i);
                //(getArgs().substr(0, getArgs().size() - i-1));
                string arg=getArgs().substr(0, getArgs().size() - i-1);
                setArgs(arg);
                sizeIsExsit = true;
            }
        }
    }
    return atoi(size.c_str());
}
