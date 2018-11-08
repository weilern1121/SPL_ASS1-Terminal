

#include <string>
#include <vector>
#include <iostream>
#include "../include/Commands.h"
using namespace std;

//constructor
LsCommand::LsCommand(string args):BaseCommand(args){};

void LsCommand::execute(FileSystem & fs) {
    Directory* initialWD= (&fs.getWorkingDirectory());
    if (this->getArgs().size() > 0) {
        bool haveSBeginning = false;

        //first- check if there is a need to go from the root
        bool isCut=false;
        if(this->getArgs().at(0)=='/') {
            fs.setWorkingDirectory(&fs.getRootDirectory());
            setArgs(getArgs().substr(1));
            isCut=true;
        }

        //check if [-s] -> remove [-s] from string and sort by size
        if (this->getArgs().size() > 1) {
            if ((this->getArgs().at(0) == '-') && (this->getArgs().at(1) == 's')) {
                setArgs(getArgs().substr(2));
                haveSBeginning = true;
            }
        }

        //find if path is exists- if not- exit the function after printing an error
        vector<string> tmpPath = convertStringToVector(getArgs());
        BaseFile* ref;
        if(tmpPath.size()==1 && tmpPath[0]!="")
            ref=findTheChild(&(fs.getWorkingDirectory()),tmpPath[0]);
        else
            ref = FindTheExactlyPlace(tmpPath, &(fs.getWorkingDirectory()));

        if (ref == nullptr || !(ref->instanceOf()))
                cout << "The system cannot find the path specified" << endl;
        else {
            //whether there is a need to re-sort, sort by name
            ((Directory*)(ref))->sortByName();

            //check if there is a need to re-sort by size
            if (haveSBeginning)
                ((Directory*)(ref))->sortBySize();

            //if the childrenVec is not empty- prnt it
            if (((Directory*)(ref))->getChildren().size() > 0)
            printChildren(*(Directory*)(ref));
            tmpPath.clear();

        }
        if(isCut)
            setArgs("/"+getArgs());
        fs.setWorkingDirectory(initialWD);
        ref= nullptr;
        initialWD= nullptr;

    }
    else {
        //if the size=0 -> need to prind this childrenVec
        //first- check if childrenVec is not empty
        if (fs.getWorkingDirectory().getChildren().size() > 0) {
            fs.getWorkingDirectory().sortByName();
            printChildren(fs.getWorkingDirectory());
        }
    }
}

void LsCommand::printChildren(Directory &dr) {
    //print in a single row every veriable of the vector
    for (size_t i = 0; i < dr.getChildren().size(); i++) {
        if (dynamic_cast<File*>(dr.getChildren()[i])) {
            cout << "FILE" << '\t' << dr.getChildren()[i]->getName() <<
                 '\t' << dr.getChildren()[i]->getSize() << endl;
        } else {
            cout << "DIR" << '\t' << dr.getChildren()[i]->getName() <<
                 '\t' << dr.getChildren()[i]->getSize() << endl;
        }
    }
}



//return the name of the function
string LsCommand::toString(){
    return "ls "+getArgs();
}
