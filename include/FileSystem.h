#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include "Files.h"


class FileSystem {
private:
	Directory* rootDirectory;
	Directory* workingDirectory;

	vector<string> convertStringToVector(string args);
	Directory* findtheworkingDirectoryPlace(Directory& newWorkingDirectory,Directory& oldWorkingDirectory);
	void copy(const FileSystem& aFileSystem);
	void move( FileSystem& aFileSystem);




		public:
	FileSystem();
	Directory& getRootDirectory() const; // Return reference to the root directory
	Directory& getWorkingDirectory() const; // Return reference to the working directory
	void setWorkingDirectory(Directory *newWorkingDirectory); // Change the working directory of the file system
	BaseFile* findTheChild(Directory* workingDir, string nameOfBaseFile);
	BaseFile* FindTheExactlyPlace(vector<string> path,Directory* workingDirectory);

	//rule of 5
	FileSystem(const FileSystem& aFileSystem);
	FileSystem(FileSystem&& aFileSystem);
	FileSystem& operator=(const FileSystem &other);
	FileSystem& operator=(FileSystem &&other);
	~FileSystem();





		//our private functions
    //Directory * duplicate(Directory * newRoot);
    //void clear();


};


#endif
