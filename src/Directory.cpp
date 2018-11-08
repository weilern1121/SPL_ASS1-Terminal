//
// Created by VailerHageverr on 13/11/17.
//
#include <string>
#include <vector>
#include "../include/Files.h"
#include "../include/GlobalVariables.h"
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;

// Constructor
Directory::Directory(string name, Directory *parent):BaseFile(name),children(),parent(parent){

}

// Return a pointer to the parent of this directory
Directory * Directory ::getParent() const {
    return parent;
}
// Return children
vector<BaseFile*>  Directory::getChildren() {
    return children;
}

void Directory::removeChildren(size_t index, bool isDeppErase) {
    if(isDeppErase)
        delete children[index];
    children[index]= nullptr;
    children.erase(children.begin()+index);
}

// Return the size of the directory (recursively)
int Directory::getSize() {
    int output=0;
    for(size_t i=0; i<children.size();i++)
        output+=children[i]->getSize();
    return output;
}

//Return the path from the root to this
string Directory::getAbsolutePath() {
    std::string output("");
        return getAbsolutePath(output);

}

string Directory::getAbsolutePath(string output) {
    if(getParent()== nullptr)
        return "";

    output=output+getParent()->getAbsolutePath(output)+"/"+getName();
    return output;

}

// Change the parent of this directory
void Directory::setParent(Directory *newParent)
{
    if(newParent!=nullptr){
        parent=newParent;
    }
}

// Add the file to children
void Directory::addFile(BaseFile* file) {
    children.insert(children.end(),file);
}

// Remove the file with the specified name from children
void Directory::removeFile(string name) {
    for(size_t i=0; i<=children.size();i++)
    {
        if(children[i]->getName()==name)
            children.erase(children.begin()+i);
    }
}

// Remove the file from children
void Directory::removeFile(BaseFile* file) {
    for(size_t i=0; i<=children.size();i++)
    {
        if(children[i]==file)
            children.erase(children.begin()+i);
    }
}
// Stable Sort children by name alphabetically (not recursively)
 void Directory::sortByName()
{
    std:: stable_sort(children.begin(), children.end() , Directory::ComparatorName());
}

// Stable Sort children by name alphabetically (not recursively)
void Directory::sortBySize()
{
    std:: stable_sort(children.begin(), children.end() , Directory::ComparatorSize());
}

    //return true if directory, false for file
    bool Directory::instanceOf() {
        return true;
    }

bool Directory::ComparatorName:: operator() ( BaseFile* f1,  BaseFile* f2)
{
    return (f1->getName() < f2->getName());
}


bool Directory::ComparatorSize:: operator() ( BaseFile* f1,  BaseFile* f2)
    {
        return (f1->getSize() < f2->getSize());
    }

//copy Constructor
Directory::Directory(const Directory& aDirectory):BaseFile(aDirectory.getName()),children(),parent(aDirectory.parent){
    if(verbose==1 || verbose==3){
        cout<<"Directory::Directory(const Directory& aDirectory)"<<endl;
    }
    for(vector<BaseFile*>::const_iterator it=aDirectory.children.begin();it!=aDirectory.children.end();++it){
        if(dynamic_cast<File*>(*it)){
            addFile(new File((*it)->getName(),(*it)->getSize()));
        } else{
            Directory* toCopy=(Directory*)(*it);
            Directory* theChild=new Directory(*toCopy);
            addFile(theChild);
        }
    }
}

//move Constructor
Directory::Directory(Directory&& aDirectory):BaseFile(aDirectory.getName()),children(std::move(aDirectory.children)),parent(){
    if(verbose==1 || verbose==3){
        cout<<"Directory::Directory(Directory&& aDirectory)"<<endl;
    }
    parent=aDirectory.parent;
    aDirectory.parent=nullptr;
    this->setName(aDirectory.getName());
    aDirectory.setName("");
}
//copy assignment operator
Directory& Directory::operator=(const Directory &other){
    if(verbose==1 || verbose==3){
        cout<<"Directory& Directory::operator=(const Directory &other)"<<endl;
    }
    if(this!=&other) {
        for (vector<BaseFile *>::const_iterator it = other.children.begin(); it != other.children.end(); ++it) {
            if (dynamic_cast<File *>(*it)) {
                addFile(new File((*it)->getName(), (*it)->getSize()));
            } else {
                Directory *toCopy = (Directory *) (*it);
                Directory *theChild = new Directory(*toCopy);
                addFile(theChild);
            }
        }
    }
    return *this;
}
//move assignment operator
Directory& Directory::operator=(Directory &&other){
    if(verbose==1 || verbose==3){
        cout<<"Directory& Directory::operator=(Directory &&other)"<<endl;
    }
    if(this!=&other) {
        this->clear();
        parent=other.parent;
        other.parent= nullptr;
        children=move(other.children);
    }
    return *this;
}

//Destructor
Directory::~Directory()
{
    if(verbose==1 || verbose==3){
        cout<<"Directory::~Directory()"<<endl;
    }
    clear();
}

void Directory::clear() {

//    for(size_t i=0; i<children.size(); i++)
//    {
//        if(children.at(i)->instanceOf())
//            delete dynamic_cast<Directory*>(children.at(i));
//        else
//            delete dynamic_cast<File*>(children.at(i));
//    }
//
//        vector<BaseFile *>::iterator it = children.begin();
//        while (it != children.end()) {
//            if (dynamic_cast<Directory *>(*it)) {
//                ((Directory *) (*it))->parent = nullptr;
//            }
//            delete (*it);
//            it = children.erase(it);
//        }
    int size=children.size();
    for(int i=0;i<size;i++){
        BaseFile *d=(children[0]);
        children.erase(children.begin());
        delete d;
    }
    children.clear();
}





