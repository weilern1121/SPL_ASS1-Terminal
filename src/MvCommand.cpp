//
// Created by weilern on 17/11/17.
//

#include <string>
#include <vector>
#include <iostream>
#include "../include/Commands.h"
using namespace std;

//constructor
MvCommand::MvCommand(string args):BaseCommand(args){};


void MvCommand::execute(FileSystem & fs){
    //step 1
    string source,dest;
    bool  flag=true;
    for(size_t i=0; i<getArgs().size() && flag; i++){
        //saperate the string for source and destination
        if (getArgs()[i]=='_'){
            source=getArgs().substr(0 , (i));
            dest=getArgs().substr(i+1);
            flag=false;
        }
    }

    //step 2 - convert to a vectors by yuval's code
    vector<string> sourceVec= convertStringToVector(source);
    vector<string> destVec= convertStringToVector(dest);

    //extract the last value from dest- because ythis is what we need to deep coppy
    if(sourceVec[0][0]=='/') {
        sourceVec[0] = sourceVec[0].substr(1);
        sourceVec.insert(sourceVec.begin(),"/");
    }

    string sourceLast= sourceVec[sourceVec.size()-1];
    sourceVec.erase(sourceVec.end());
    //step 3
    BaseFile *pathDest;
    if(destVec[0][0]=='/'){
        destVec[0]=destVec[0].substr(1);
        if(destVec.size()==1 && destVec[0]=="")
            pathDest=&fs.getRootDirectory();
        else
            pathDest = FindTheExactlyPlace(destVec, &fs.getRootDirectory());
    }
    else
        pathDest = FindTheExactlyPlace(destVec, &fs.getWorkingDirectory());
    BaseFile *pathSource;
    if(sourceVec[0][0]=='/'){
        sourceVec[0]=sourceVec[0].substr(1);
        if (sourceVec.size() == 1&& sourceVec[0]=="")
            pathSource=&fs.getRootDirectory();
        else
        pathSource = FindTheExactlyPlace(sourceVec, &fs.getRootDirectory());
    }
    else {
        pathSource = FindTheExactlyPlace(sourceVec, &fs.getWorkingDirectory());
    }
    if(pathSource== nullptr || !(pathSource->instanceOf()) || pathDest == nullptr ||  !(pathDest->instanceOf()))
        cout << "No such file or directory" << endl;

        //step 4
    else{
        BaseFile* toMove=findTheChild(dynamic_cast<Directory*>(pathSource),sourceLast);
        if(toMove== nullptr)
            cout << "No such file or directory" << endl;
        else {
            //this sitution is the forbid move the WorkingDirectory
            if (!(legalPathWorkingDirectory(*(dynamic_cast<Directory *>(toMove)),
                                            (dynamic_cast<Directory *>(&fs.getWorkingDirectory())),
                                            fs.getRootDirectory())))
                std::cout << "Can't move directory" << endl;
            else {
                //if toMove is instanceOf directory- change his directory* pointer/
                //this is the only difference between dirtory and file.
                if (toMove == &fs.getWorkingDirectory())
                    cout << "Can't move directory" << endl;
                else {
                    if (toMove->instanceOf())
                        dynamic_cast<Directory *>(toMove)->setParent(dynamic_cast<Directory *>(pathDest));

                    dynamic_cast<Directory *>(pathDest)->addFile(toMove);
                    //find the place of the moved file
                    for (size_t i = 0; i < (dynamic_cast<Directory *>(pathSource))->getChildren().size(); i++) {
                        if (dynamic_cast<Directory *>(pathSource)->getChildren()[i] == toMove) {
                            //first- set the pointer to point on nullptr and then delete him
                            ((Directory *) (pathSource))->removeChildren(i, false);
                            //delete(((Directory *)(pathSource))->getChildren()[i]);
                            //(dynamic_cast<Directory *>(pathSource))->getChildren().erase((dynamic_cast<Directory *>(pathSource))->getChildren().begin()+i);
                        }
                    }
                }
            }
        }
    }
    //delete
    sourceVec.clear();
    destVec.clear();
    pathSource= nullptr;
    pathDest= nullptr;

}


string MvCommand::toString(){
    string output=getArgs();
    switchSpaceToLine(&output);
    return "mv "+output;
}
