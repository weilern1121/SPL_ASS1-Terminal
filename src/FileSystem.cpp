//
// Created by yyarom on 12/11/17.
//
#include "../include/FileSystem.h"
#include "../include/GlobalVariables.h"
#include <iostream>
#include <sstream>
#include <string>



//   Directory* rootDirectory;
//   Directory* workingDirectory;

//constructor
FileSystem::FileSystem():rootDirectory(new Directory("root", nullptr)),workingDirectory(rootDirectory)
{

}

// Return reference to the root directory
Directory& FileSystem::getRootDirectory() const{
    return *rootDirectory;
}

// Return reference to the working directory
Directory& FileSystem::getWorkingDirectory() const{
    return *workingDirectory;
}

// Change the working directory of the file system
void FileSystem::setWorkingDirectory(Directory *newWorkingDirectory){
    if(newWorkingDirectory!= nullptr){
        this->workingDirectory=newWorkingDirectory;
    }

}

void FileSystem::copy(const FileSystem& aFileSystem){
    rootDirectory=new Directory(*aFileSystem.rootDirectory);
    workingDirectory=findtheworkingDirectoryPlace(*rootDirectory,*aFileSystem.workingDirectory);
}
void FileSystem::move( FileSystem& aFileSystem){
    rootDirectory=&aFileSystem.getRootDirectory();
    workingDirectory=&aFileSystem.getWorkingDirectory();

    aFileSystem.rootDirectory= nullptr;
    aFileSystem.workingDirectory= nullptr;
}

Directory* FileSystem::findtheworkingDirectoryPlace(Directory& newWorkingDirectory,Directory& oldWorkingDirectory){
    vector<string> path= convertStringToVector(oldWorkingDirectory.getAbsolutePath());
    //reverse(path.begin(),path.end());
    BaseFile* tmp=FindTheExactlyPlace(path,&newWorkingDirectory);
    if(dynamic_cast<Directory*>(tmp))
        return (dynamic_cast<Directory*>(tmp));
    else
        return nullptr;
}

vector<string> FileSystem::convertStringToVector(string args){

    //create the output
    vector<string> output;

    //case addition- id args is empty
    if(args.compare("")==0)
        return output;
    if(args[0]=='/')
        args=args.substr(1);

    size_t i=0;

    while(i<args.length()) {
        //cut the string and push it to the vector
        if(args.at(i)=='/') {
            if(i>0) {
                output.push_back(args.substr(0,i));
                args=args.substr(i+1);
                i=0;
            }
        }
        i++;
    }
    output.push_back(args);
    return (output);
}

//this function find the pointer to the correct child. if not exsist return null.
BaseFile* FileSystem::findTheChild(Directory* workingDir, string nameOfBaseFile){
    for(size_t i=0;i<workingDir->getChildren().size();i++){
        if(workingDir->getChildren()[i]->getName()==nameOfBaseFile)
            return workingDir->getChildren()[i];
    }
    return nullptr;
}

BaseFile* FileSystem::FindTheExactlyPlace(vector<string> path,Directory* workingDirectory) {
    BaseFile *tmp;
    if(path.size()==0) {
        //   BaseFile *tmp=(BaseFile)workingDirectory;
        return workingDirectory;
    }
    while (path.size() > 0) {
        //mybe change to reference
        tmp = findTheChild(workingDirectory, path[0]);
        //if not found return null
        if (tmp == nullptr) {
            return tmp;
        }
        else {
            //if is file and ther are more path than the path incorrect
            if (dynamic_cast<File*>(tmp) && path.size() > 1)
                return nullptr;
                //if last file of the adress is
            else if (dynamic_cast<File*>(tmp) && path.size() == 1)
                return tmp;
            else {
                //if the path is directory
                path.erase(path.begin());
                workingDirectory = (dynamic_cast<Directory*>(tmp));
            }
        }
    }
    return tmp;
}
//copy Constructor
FileSystem::FileSystem(const FileSystem& aFileSystem):rootDirectory(),workingDirectory(){
    if(verbose==1 || verbose==3){
        cout<<"FileSystem::FileSystem(const FileSystem& aFileSystem)"<<endl;
    }
    copy(aFileSystem);
}
//move Constructor
FileSystem::FileSystem(FileSystem&& aFileSystem):rootDirectory(),workingDirectory(){
    if(verbose==1 || verbose==3){
        cout<<"FileSystem::FileSystem(FileSystem&& aFileSystem)"<<endl;
    }
    move(aFileSystem);
}

//copy assignment operator
FileSystem& FileSystem::operator=(const FileSystem &other){
    if(verbose==1 || verbose==3){
        cout<<"FileSystem& FileSystem::operator=(const FileSystem &other)"<<endl;
    }
    if(this!=&other) {
        copy(other);
    }
    return *this;

}
//move assignment operator
FileSystem& FileSystem::operator=(FileSystem &&other){
    if(verbose==1 || verbose==3)
        cout<<"FileSystem::~FileSystem()"<<endl;
        if(this!=&other)
            move(other);
    return *this;

}
FileSystem::~FileSystem(){
    if(verbose==1 || verbose==3){
        cout<<"FileSystem::~FileSystem()"<<endl;
    }
    delete rootDirectory;
    workingDirectory= nullptr;
    rootDirectory= nullptr;
}



