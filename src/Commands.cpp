//
// Created by yyarom on 12/11/17.
//
#include "../include/Commands.h"
#include <ios>

    BaseCommand::BaseCommand(string args):args(args)
    {
    }

//i add const to getargs
string BaseCommand:: getArgs()const
{
    return args;
}

    //Destructor
    BaseCommand:: ~BaseCommand()
    {
    }

    //copy Constructor
    BaseCommand::BaseCommand(const BaseCommand &basecom):args()
    {
            this->args.erase();
            this->args=basecom.args;
    }
    //copy assignment operator
    BaseCommand& BaseCommand::operator =(const BaseCommand &basecom)
    {
        // check for "self assignment" and do nothing in that case
        if (this == &basecom) {
            return *this;
        }

        this->args=basecom.args;
        return *this;
    }

    void BaseCommand::setArgs(string otherArgs)
    {
        args.clear();
        this->args=otherArgs;
    }

    vector<string> BaseCommand:: convertStringToVector(string args){
    //remove all the spaces from args
    //remove(args.begin(), args.end(), " ");

    //create the output
    vector<string> output;

        //case addition- id args is empty
        if(args.compare("")==0)
            return output;

    size_t i=0;
    //if(output.front()=="/"){
     //   return (output);
    //}

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
    BaseFile* BaseCommand::findTheChild(Directory* workingDir, string nameOfBaseFile){
    for(size_t i=0;i<workingDir->getChildren().size();i++){
        if(workingDir->getChildren()[i]->getName()==nameOfBaseFile)
            return workingDir->getChildren()[i];
    }
    //if not found- there is a chance that need to return the father by ..
    if(nameOfBaseFile.compare("..")==0)
        return workingDir->getParent();
    return nullptr;
}

BaseFile* BaseCommand::FindTheExactlyPlace(vector<string> path,Directory* workingDirectory) {
    BaseFile *tmp;
    if(path.size()==0) {
     //   BaseFile *tmp=(BaseFile)workingDirectory;
       return workingDirectory;
    }
    while (path.size() > 0) {
        if (path[0]=="..") {
            if (workingDirectory->getParent() == nullptr)
                return nullptr;
            else {
                workingDirectory = (workingDirectory->getParent());
                path.erase(path.begin());
            }
        } else {
            tmp = findTheChild(workingDirectory, path[0]);
            //if not found return null
            if (tmp == nullptr) {
                return tmp;
            } else {
                //if is file and ther are more path than the path incorrect
                if (dynamic_cast<File *>(tmp) && path.size() > 1)
                    return nullptr;
                    //if last file of the adress is
                else if (dynamic_cast<File *>(tmp) && path.size() == 1)
                    return tmp;
                else {
                    //if the path is directory
                    path.erase(path.begin());
                    workingDirectory = (dynamic_cast<Directory *>(tmp));
                }
            }
        }
    }
    return workingDirectory;
}

bool BaseCommand::legalPathWorkingDirectory(Directory& fToRemove,Directory* WorkingDirectory, Directory& rootDirectory){
    Directory* initialWD= WorkingDirectory;
    bool output=true;
    bool thereAreMoreWayUp=true;

    while(thereAreMoreWayUp && output){
        if((initialWD)==(&(fToRemove)))
            output=false;
        if(initialWD->getParent()!= nullptr){
            initialWD = initialWD->getParent();
        }
        else
         thereAreMoreWayUp=false;
    }
   // WorkingDirectory=initialWD;
    //initialWD= nullptr;
    return output;
}

void BaseCommand::switchSpaceToLine (string* input) {
    if(*input!="") {
        bool isFirstSpace = true;
        size_t i = 0;
        while (i < input->size()) {
            if (input->at(i) == '_' && !(isFirstSpace))
                input->erase(i);
            else {
                if (input->at(i) == '_' && isFirstSpace) {
                    input->at(i) = ' ';
                    isFirstSpace = false;
                }
                i++;
            }
        }
    }
}



