#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <string>
#include "FileSystem.h"


class BaseCommand {
private:
	string args;

public:
	BaseCommand(string args);
	string getArgs()const;
	virtual void execute(FileSystem & fs) = 0;
	virtual string toString() = 0;

	//private functions
	BaseCommand(const BaseCommand &basecom);//copy Constructor
	BaseCommand& operator =(const BaseCommand &basecom);//copy assignment operator
	virtual ~BaseCommand();	//Destructor

protected:
    //.our functions
    void setArgs(string otherArgs);
    vector<string> convertStringToVector(string args);
    BaseFile* findTheChild(Directory* workingDir, string nameOfBaseFile);
    BaseFile* FindTheExactlyPlace(vector<string> path,Directory* workingDirectory);
    bool legalPathWorkingDirectory(Directory& fToRemove,Directory* WorkingDirectory,Directory& rootDirectory);
	void switchSpaceToLine (string* input);

};



class PwdCommand : public BaseCommand {
private:
public:
	PwdCommand(string args);
	void execute(FileSystem & fs); // Every derived class should implement this function according to the document (pdf)
	virtual string toString();

};

class CdCommand : public BaseCommand {
private:
public:
	CdCommand(string args);
    void execute(FileSystem & fs);
	string toString();
};

class LsCommand : public BaseCommand {
private:
	void printChildren(Directory & dr);
public:
	LsCommand(string args);
    void execute(FileSystem & fs);
	string toString();
};

class MkdirCommand : public BaseCommand {
private:
public:
	MkdirCommand(string args);
	void execute(FileSystem & fs);
	string toString();
    //our functions
    string goToTrip(Directory* dir);
    };

class MkfileCommand : public BaseCommand {
private:
    int  cutTheSize();

public:
	MkfileCommand(string args);
	void execute(FileSystem & fs);
	string toString();
};

class CpCommand : public BaseCommand {
private:
	void copyTheDir(Directory* source, Directory* dest);

public:
	CpCommand(string args);
    void execute(FileSystem & fs);
	string toString();
};

class MvCommand : public BaseCommand {
private:
public:
	MvCommand(string args);
	void execute(FileSystem & fs);
	string toString();
};

class RenameCommand : public BaseCommand {
private:
    //our functions
    string rescueTheFileName(string args);

public:
	RenameCommand(string args);
    void execute(FileSystem & fs);
	string toString();
};

class RmCommand : public BaseCommand {
private:
    //our functions
    void recursivelyRemove(Directory* rootToRemove);

        public:
	RmCommand(string args);
	void execute(FileSystem & fs);
	string toString();
};

class HistoryCommand : public BaseCommand {
private:
	const vector<BaseCommand *> & history;
public:
	HistoryCommand(string args, const vector<BaseCommand *> & history);
	void execute(FileSystem & fs);
	string toString();
};


class VerboseCommand : public BaseCommand {
private:
public:
	VerboseCommand(string args);
	void execute(FileSystem & fs);
	string toString();
};

class ErrorCommand : public BaseCommand {
private:
public:
	ErrorCommand(string args);
    void execute(FileSystem & fs);
	string toString();
};

class ExecCommand : public BaseCommand {
private:
	const vector<BaseCommand *> & history;
public:
	ExecCommand(string args, const vector<BaseCommand *> & history);
	void execute(FileSystem & fs);
    vector<BaseCommand *> getHistory();
	string toString();
};


#endif
