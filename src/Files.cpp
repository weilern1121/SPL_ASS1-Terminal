//
// Created by yyarom on 12/11/17.
//
#include "../include/Files.h"
using namespace std;



//class File : public BaseFile {
//private:
//    int size;

//public:
    File::File(string name, int size):BaseFile(name),size(size)
    {
    }

    void File::setSize(int num)
    {
        size=num;
    }

    int File ::getSize()
    {
        return size;
    }
    //Destructor
    File:: ~File()
    {
    }
    //copy Construcor
    File::File(const File &aFile):BaseFile(aFile.getName()),size() {
        setSize(aFile.size);
    }

    //copy assigment operator
    File& File::operator=(const File &other)
    {
        if(this !=&other){
            //maybe need to delete name
            setName(other.getName());
            size=other.size;
        }
        return *this;
    }
     //return true if directory, false for file
     bool File:: instanceOf(){
         return false;
     }
    //move constractor
    void File::clear(){

    }





