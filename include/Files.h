#ifndef FILES_H_
#define FILES_H_

#include <string>
#include <vector>
using namespace std;

class BaseFile {
private:
	string name;

public:
	BaseFile(string name);
	virtual ~BaseFile();
	string getName() const;
	void setName(string newName);
	virtual int getSize() = 0;
	//i add the next function
	virtual bool instanceOf()=0;
	virtual void clear()=0;

};

class File : public BaseFile {
private:
	int size;

public:
	File(string name, int size); // Constructor
	int getSize(); // Return the size of the file
	void setSize(int num); //set a new size
	~File();
	File(const File &aFile);//copy Constructor
	File& operator=(const File &other); //copy assignment operator

    //our private functions
	bool instanceOf(); //return true if directory, false for file
	void clear();

};

class Directory : public BaseFile {
private:
	vector<BaseFile*> children;
	Directory *parent;
	void swap(int i,int j);
	string getAbsolutePath(string st);

	//our functions
	static int compName (Directory& a,Directory& b);
    static int compSize (Directory& a,Directory& b);
	void copyTheDir(Directory& source, Directory* dest);
	Directory&  getChildrenAt(int i, Directory& dr);


public:
	Directory(string name, Directory *parent); // Constructor
	Directory *getParent() const; // Return a pointer to the parent of this directory
	void setParent(Directory *newParent); // Change the parent of this directory
	void addFile(BaseFile* file); // Add the file to children
	void removeFile(string name); // Remove the file with the specified name from children
	void removeFile(BaseFile* file); // Remove the file from children
	vector<BaseFile*> getChildren(); // Return children
	int getSize(); // Return the size of the directory (recursively)
	string getAbsolutePath();  //Return the path from the root to this

	//our functions
	void sortByName(); // Sort children by name alphabetically (not recursively)
	void sortBySize(); // Sort children by size (not recursively)
	bool instanceOf(); //return true if directory, false for file
	void removeChildren(size_t index, bool isDeppErase);

    //rule of 5
    Directory(const Directory& aDirectory);
    Directory(Directory&& aDirectory);
    Directory& operator=(const Directory &other);
    Directory& operator=(Directory &&other);
    ~Directory();
    void clear();	//deep-destructor


    class ComparatorName {
    public:
        bool operator()(BaseFile *f1, BaseFile *f2);
    };

    class ComparatorSize {
    public:
        bool operator()(BaseFile *f1, BaseFile *f2);
    };

};


#endif

