#include<iostream>
#include<cmath>
#include<windows.h>
#include<fstream>
#include<string>
#include <ctime>
using namespace std;
class File
{
    public:
    string name;
    string Extension;
    int size;
    chrono::system_clock::time_point CreationTime;
    time_t CreationDate;
    File(string name="",string exe="txt",int size=10)
    {
        this->name=name;
        Extension=exe;
        this->size=size;
        CreationTime = chrono::system_clock::now();
        CreationDate = chrono::system_clock::to_time_t(CreationTime);
    }
};
