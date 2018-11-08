//
// Created by yyarom on 12/11/17.
//
#include "../include/Environment.h"
#include "../include/GlobalVariables.h"
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

//constructor
Environment::Environment():commandsHistory(vector<BaseCommand*>()),fs(){
//    commandsHistory=;
}

// Get a reference to the file system
FileSystem& Environment::getFileSystem() const{
    return (FileSystem &) fs;
}

// Add a new command to the history
void Environment::addToHistory(BaseCommand *command){
    if(command!=nullptr)
    commandsHistory.push_back(command);
}

// Return a reference to the history of commands
const vector<BaseCommand*>& Environment::getHistory() const{
    return commandsHistory;
}


void Environment::start() {

    bool notExit = true;
    string *input =  new string();

    while (notExit) {
        //step 1- print hello
        if(&fs.getWorkingDirectory()==&fs.getRootDirectory()){
            std::cout << "/>";
            //fs.setWorkingDirectory(&fs.getRootDirectory());
        }
        else
            std::cout << fs.getWorkingDirectory().getAbsolutePath() << ">";

        //step 2 - inpout
        getline(cin,*input);

        //verbose check
        if(verbose==2 || verbose==3)
            std::cout<<*input<<endl;

        //step3- processing the string
        cutTheStart(input);

        //check if legal input size
        if(input->size()<2){
            // ErrorCommand err;
            ErrorCommand *err = new ErrorCommand(*input);
            addToHistory(err);
            (*err).execute(getFileSystem());
        }
            //step4- find kind of the exact command
        else{
            //pwd command
            if (input->at(0) == 'p' && input->at(1) == 'w' && input->at(2) == 'd') {
                (*input) = input->substr(3);
                cutTheStart(input);
                cutTheEnd(input);
                switchSpaceToLine(input);
                PwdCommand *pwd = new PwdCommand(*input);
                addToHistory(pwd);
                (*pwd).execute(getFileSystem());
            } else {
                //cd command
                if (input->at(0) == 'c' && input->at(1) == 'd') {
                    (*input) = input->substr(2);
                    cutTheStart(input);
                    cutTheEnd(input);
                    switchSpaceToLine(input);
                    CdCommand *cd = new CdCommand(*input);
                    addToHistory(cd);
                    (*cd).execute(getFileSystem());
                } else {
                    //ls command
                    if (input->at(0) == 'l' && input->at(1) == 's') {
                        (*input) = input->substr(2);
                        cutTheStart(input);
                        cutTheEnd(input);
                        switchSpaceToLine(input);
                        LsCommand *ls = new LsCommand(*input);
                        addToHistory(ls);
                        (*ls).execute(getFileSystem());
                    } else {
                        //mkdir command
                        if (input->at(0) == 'm' && input->at(1) == 'k' && input->at(2) == 'd' && input->at(3) == 'i' &&
                            input->at(4) == 'r') {
                            (*input) = input->substr(5);
                            cutTheStart(input);
                            cutTheEnd(input);
                            switchSpaceToLine(input);
                            MkdirCommand *mkdir = new MkdirCommand(*input);
                            addToHistory(mkdir);
                            (*mkdir).execute(getFileSystem());
                        } else {
                            //mkfile command
                            if (input->at(0) == 'm' && input->at(1) == 'k' && input->at(2) == 'f' && input->at(3) == 'i' &&
                                input->at(4) == 'l' && input->at(5) == 'e') {
                                (*input) = input->substr(6);
                                cutTheStart(input);
                                cutTheEnd(input);
                                switchSpaceToLine(input);
                                MkfileCommand *mkfile = new MkfileCommand(*input);
                                addToHistory(mkfile);
                                (*mkfile).execute(getFileSystem());
                            } else {
                                //cp command
                                if (input->at(0) == 'c' && input->at(1) == 'p') {
                                    (*input) = input->substr(2);
                                    cutTheStart(input);
                                    cutTheEnd(input);
                                    switchSpaceToLine(input);
                                    CpCommand *cp = new CpCommand(*input);
                                    addToHistory(cp);
                                    (*cp).execute(getFileSystem());
                                } else {
                                    //mv command
                                    if (input->at(0) == 'm' && input->at(1) == 'v') {
                                        (*input) = input->substr(2);
                                        cutTheStart(input);
                                        cutTheEnd(input);
                                        switchSpaceToLine(input);
                                        MvCommand *mv = new MvCommand(*input);
                                        addToHistory(mv);
                                        (*mv).execute(getFileSystem());
                                    } else {
                                        //rename command
                                        if (input->at(0) == 'r' && input->at(1) == 'e' && input->at(2) == 'n' &&
                                            input->at(3) == 'a' && input->at(4) == 'm' && input->at(5) == 'e') {
                                            (*input) = input->substr(6);
                                            cutTheStart(input);
                                            cutTheEnd(input);
                                            switchSpaceToLine(input);
                                            RenameCommand *rename = new RenameCommand(*input);
                                            addToHistory(rename);
                                            (*rename).execute(getFileSystem());
                                        } else {
                                            //rm command
                                            if (input->at(0) == 'r' && input->at(1) == 'm') {
                                                (*input) = input->substr(2);
                                                cutTheStart(input);
                                                cutTheEnd(input);
                                                switchSpaceToLine(input);
                                                RmCommand *rm = new RmCommand(*input);
                                                addToHistory(rm);
                                                (*rm).execute(getFileSystem());
                                            } else {
                                                //history command
                                                if (input->at(0) == 'h' && input->at(1) == 'i' && input->at(2) == 's' &&
                                                    input->at(3) == 't' && input->at(4) == 'o' && input->at(5) == 'r' &&
                                                    input->at(6) == 'y') {
                                                    (*input) = input->substr(7);
                                                    cutTheStart(input);
                                                    cutTheEnd(input);
                                                    switchSpaceToLine(input);
                                                    HistoryCommand *history = new HistoryCommand(*input, getHistory());
                                                    (*history).execute(getFileSystem());
                                                    addToHistory(history);
                                                } else {
                                                    //verbose command
                                                    if (input->at(0) == 'v' && input->at(1) == 'e' && input->at(2) == 'r' &&
                                                        input->at(3) == 'b' && input->at(4) == 'o' && input->at(5) == 's' &&
                                                        input->at(6) == 'e') {
                                                        (*input) = input->substr(7);
                                                        cutTheStart(input);
                                                        cutTheEnd(input);
                                                        switchSpaceToLine(input);
                                                        VerboseCommand* verbose=new VerboseCommand(*input);
                                                        addToHistory(verbose);
                                                        (*verbose).execute(getFileSystem());
                                                    } else {
                                                        //exec command
                                                        if (input->at(0) == 'e' && input->at(1) == 'x' &&
                                                            input->at(2) == 'e' && input->at(3) == 'c') {
                                                            (*input) = input->substr(4);
                                                            cutTheStart(input);
                                                            cutTheEnd(input);
                                                            switchSpaceToLine(input);
                                                            ExecCommand *exec = new ExecCommand(*input, getHistory());
                                                            addToHistory(exec);
                                                            (*exec).execute(getFileSystem());
                                                        } else {
                                                            //exit command
                                                            if (input->at(0) == 'e' && input->at(1) == 'x' &&
                                                                input->at(2) == 'i' && input->at(3) == 't') {
                                                                notExit = false;
                                                            } else {
                                                                // ErrorCommand err;
                                                                ErrorCommand *err = new ErrorCommand(*input);
                                                                addToHistory(err);
                                                                (*err).execute(getFileSystem());
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    delete input;

}

void Environment::cutTheStart (string* input) {
    if(*input!="")
    {
        size_t i=0;
         //input->replace(input->begin(),input->end(), "    ",' ');
        while(i<input->size() && (input->at(i)==' ' ||input->at(i)==9))
            i++;

        (*input)=input->substr(i);
    }
}

void Environment::cutTheEnd (string* input) {
    if(*input!="") {
        size_t i = input->size() - 1;
        while (input->at(i) == ' ' || input->at(i)==9)
            i--;
        (*input) = input->substr(0, i+1);
    }
}

void Environment::switchSpaceToLine (string* input) {
    if(*input!="") {
        bool isFirstSpace = true;
        size_t i = 0;
        while (i < input->size()) {
            if (input->at(i) == ' ' && !(isFirstSpace))
                input->erase(i);
            else {
                if (input->at(i) == ' ' && isFirstSpace) {
                    input->at(i) = '_';
                    isFirstSpace = false;
                }
                i++;
            }
        }
    }
}
//Destructor
Environment::~Environment(){
    if(verbose==1 || verbose==3){
        cout<<"Environment::~Environment()"<<endl;
    }
//    vector<BaseCommand*>::iterator it=commandsHistory.begin();
//    while(it!=commandsHistory.end()){
//        delete(*it);
//        it=commandsHistory.erase(it);

    size_t size=commandsHistory.size();
    for(size_t i=0;i<size;i++){
        BaseCommand *d= (commandsHistory[0]);
        commandsHistory.erase(commandsHistory.begin());
        delete d;
    }
    commandsHistory.clear();
    //delete &fs;
}




//move Constructor
Environment::Environment(Environment&& Environment):commandsHistory() , fs(){
    if(verbose==1 || verbose==3){
        cout<<"Environment::Environment(Environment&& Environment)"<<endl;
    }
    commandsHistory=move(Environment.commandsHistory);
    fs= *move(&Environment.fs) ;
}

////copy assignment operator
Environment& Environment::operator = (const Environment &other){
    if(verbose==1 || verbose==3){
        cout<<"Environment& Environment::operator = (const Environment &other)"<<endl;
    }
    if(this!=&other){
        copy(other);
    }
    return *this;
}

//copy Constructor
Environment::Environment(const Environment& aEnvironment):commandsHistory() , fs(){
    if(verbose==1 || verbose==3){
        cout<<"Environment::Environment(const Environment& aEnvironment)"<<endl;
    }
    copy(aEnvironment);
}

Environment& Environment::operator=(Environment &&other)
{
    if(verbose==1||verbose==3)
        std::cout <<fs.getWorkingDirectory().getAbsolutePath()<< "Environment& Environment::operator=(Environment &&other)" <<endl;

    if(this!=&other){
        move(other);
    }
return *this;
}

void Environment::copy(const Environment& aEnvironment) {
    for (vector<BaseCommand *>::const_iterator it = aEnvironment.commandsHistory.begin(); it != aEnvironment.commandsHistory.end(); ++it) {
        if(dynamic_cast<PwdCommand*>(*it))
            commandsHistory.push_back(new PwdCommand(((PwdCommand*)(*it))->getArgs()));
        if(dynamic_cast<CdCommand*>(*it))
            commandsHistory.push_back(new CdCommand(((CdCommand*)(*it))->getArgs()));
        if(dynamic_cast<LsCommand*>(*it))
            commandsHistory.push_back(new LsCommand(((LsCommand*)(*it))->getArgs()));
        if(dynamic_cast<MkdirCommand*>(*it))
            commandsHistory.push_back(new MkdirCommand(((MkdirCommand*)(*it))->getArgs()));
        if(dynamic_cast<MkfileCommand*>(*it))
            commandsHistory.push_back(new MkfileCommand(((MkfileCommand*)(*it))->getArgs()));
        if(dynamic_cast<CpCommand*>(*it))
            commandsHistory.push_back(new CpCommand(((CpCommand*)(*it))->getArgs()));
        if(dynamic_cast<MvCommand*>(*it))
            commandsHistory.push_back(new MvCommand(((MvCommand*)(*it))->getArgs()));
        if(dynamic_cast<RenameCommand*>(*it))
            commandsHistory.push_back(new RenameCommand(((RenameCommand*)(*it))->getArgs()));
        if(dynamic_cast<RmCommand*>(*it))
            commandsHistory.push_back(new RmCommand(((RmCommand*)(*it))->getArgs()));
        if(dynamic_cast<HistoryCommand*>(*it))
            commandsHistory.push_back(new HistoryCommand(((HistoryCommand*)(*it))->getArgs(),(aEnvironment.commandsHistory)));
        if(dynamic_cast<ExecCommand*>(*it))
            commandsHistory.push_back(new ExecCommand(((ExecCommand*)(*it))->getArgs(),(aEnvironment.commandsHistory)));
//        if(dynamic_cast<VerboseCommand*>(*it))
//            commandsHistory.push_back(new VerboseCommand(((VerboseCommand*)(*it))->getArgs()));
    }
    fs=*(new FileSystem(aEnvironment.fs));
}





