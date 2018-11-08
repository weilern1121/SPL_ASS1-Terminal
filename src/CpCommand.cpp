//
// Created by weilern on 17/11/17.
//

#include <string>
#include <vector>
#include <iostream>
#include "../include/Commands.h"
using namespace std;

//constructor
CpCommand::CpCommand(string args):BaseCommand(args){};


void CpCommand::execute(FileSystem & fs){

    //step 1
    string source,dest;
    bool flag=true;
    for(size_t i=0; i<getArgs().size() && flag; i++){
        //saperate the string for source and destination
        if (getArgs()[i]=='_'){
            source=getArgs().substr(0 , (i));
            dest=getArgs().substr(i+1);
            flag=false;
        }
    }
    if(source=="")
        source=getArgs();

    //step 2 - convert to a vectors of strings that every cell represent a name of dir/file
    vector<string> sourceVec= convertStringToVector(source);
    vector<string> destVec= convertStringToVector(dest);

    //extract the last value from dest- because ythis is what we need to deep coppy
    string sourceLast= sourceVec[sourceVec.size()-1];
    sourceVec.erase(sourceVec.end());

    BaseFile *pathDest;
    //step 3 jump to dest and source

    if (destVec[0] == "/") {
        destVec.erase(destVec.begin());
        pathDest = FindTheExactlyPlace(destVec, &fs.getRootDirectory());
    } else {
        pathDest = FindTheExactlyPlace(destVec, &fs.getWorkingDirectory());
    }
    BaseFile *pathSource;
    if(sourceVec[0] == "/" && sourceVec.size()>1){
        sourceVec.erase(destVec.begin());
        pathSource = FindTheExactlyPlace(sourceVec, &fs.getRootDirectory());
    }
    else{
        pathSource = FindTheExactlyPlace(sourceVec, &fs.getWorkingDirectory());
    }

    if(pathSource== nullptr || !(pathSource->instanceOf()) || pathDest == nullptr ||  !(pathDest->instanceOf()))
        std::cout << "No such file or directory" << endl;

        //step 4
    else{
        //find the exect bafefile to copy
        pathSource=findTheChild(dynamic_cast<Directory*>(pathSource),sourceLast);
        if(pathSource== nullptr)
            cout << "No such file or directory" << endl;

        else {
            if(findTheChild(dynamic_cast<Directory*>(pathDest),sourceLast)!= nullptr){
                ;
                }
            else {
                if (!(pathSource->instanceOf()) && dynamic_cast<File *>(pathSource)) {
                    dynamic_cast<Directory*>(pathDest)->addFile(new File(sourceLast, ((File*)(pathSource))->getSize()));
                }

                else {
                    Directory* toCoppyD=new Directory(*(dynamic_cast<Directory*>(pathSource)));
                    toCoppyD->setParent(dynamic_cast<Directory*>(pathSource));
                    dynamic_cast<Directory*>(pathDest)->addFile(toCoppyD);
                    }
                }
            }
        }
    //delete
    pathSource= nullptr;
    pathDest= nullptr;

}

//return the name of the function
string CpCommand::toString(){
    string output=getArgs();
    switchSpaceToLine(&output);
    return "cp "+output;
}

