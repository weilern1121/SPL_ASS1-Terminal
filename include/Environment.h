#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "Files.h"
#include "Commands.h"

#include <string>
#include <vector>

using namespace std;

class Environment {
private:
	vector<BaseCommand*> commandsHistory;
	FileSystem fs;

	//our funstions
	void cutTheStart(string* input);
    void switchSpaceToLine(string* input);
    void cutTheEnd(string* input);




public:
	Environment();
	void start();
	FileSystem& getFileSystem() const; // Get a reference to the file system
	void addToHistory(BaseCommand *command); // Add a new command to the history
	const vector<BaseCommand*>& getHistory() const; // Return a reference to the history of commands
	virtual ~Environment();	//Destructor
	Environment(const Environment& aEnvironment);
	void copy(const Environment& aEnvironment);
	Environment(Environment&& Environment);
	Environment& operator = (const Environment &other);
    Environment &operator = ( Environment &&other);//move assignment operator


	};

#endif
