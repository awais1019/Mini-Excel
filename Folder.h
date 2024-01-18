#include <iostream>
#include <conio.h>
#include <cmath>
#include <windows.h>
#include <fstream>
#include <string>
#include <ctime>
#include <list>
#include <chrono>
#include <iomanip>
#include "File.h"
using namespace std;
class Folder
{
public:
    string name;
    Folder *Parent;
    list<Folder *> SubFolders;
    list<File *> SubFiles;
    string path;
    chrono::system_clock::time_point CreationTime;
    time_t CreationDate;
    Folder(string name = "", Folder *parent = nullptr, string path = "")
    {
        this->name = name;
        Parent = parent;
        this->path = path;
        SubFolders = list<Folder *>();
        SubFiles = list<File *>();
        CreationTime = chrono::system_clock::now();
        CreationDate = chrono::system_clock::to_time_t(CreationTime);
    }
    void AddFolder(Folder *folder)
    {
        SubFolders.push_back(folder);
    }
    void AddFile(File *file)
    {
        SubFiles.push_back(file);
    }
    void PrintDir()
    {
        list<Folder *>::iterator it;
        int countdir = 0;
        for (it = SubFolders.begin(); it != SubFolders.end(); it++)
        {
            auto creationTime = chrono::system_clock::to_time_t((*it)->CreationTime);
            cout << put_time(localtime(&creationTime), "%m/%d/%Y  %I:%M %p");
            cout << "\t<DIR>\t";
            cout << (*it)->name << endl;
            countdir++;
        }

        list<File *>::iterator fi;
        int countfiles = 0;
        for (fi = SubFiles.begin(); fi != SubFiles.end(); fi++)
        {
            auto creationTime = chrono::system_clock::to_time_t((*fi)->CreationTime);
            cout << put_time(localtime(&creationTime), "%m/%d/%Y  %I:%M %p\t\t");
            cout << (*fi)->name << (*fi)->Extension << "   \t" << (*fi)->size << "kb" << endl;
            countfiles++;
        }
        cout << "\t\t" << countfiles << " File(s)\n";
        cout << "\t\t" << countdir << " Dir(s)\n";
    }
    Folder *IsExitDir(string Name)
    {
        list<Folder *>::iterator it;
        for (it = SubFolders.begin(); it != SubFolders.end(); it++)
        {
            if ((*it)->name == Name)
            {
                return (*it);
            }
        }
        return nullptr;
    }
    File *IsExitFile(string Name, string exe)
    {
        list<File *>::iterator it;
        for (it = SubFiles.begin(); it != SubFiles.end(); it++)
        {
            if ((*it)->name == Name && (*it)->Extension == exe)
            {
                return (*it);
            }
        }
        return nullptr;
    }

    void RemoveDir(Folder *dir)
    {
        SubFolders.remove(dir);
    }
    void RemoveFile(File *file)
    {
        SubFiles.remove(file);
    }
    bool CheckFileEXE(string exe)
    {
        list<File *>::iterator it;
        for (it = SubFiles.begin(); it != SubFiles.end(); it++)
        {
            if ((*it)->Extension == exe)
            {
                return true;
                ;
            }
        }
        return false;
    }
    Folder *CheckDirectory(string dir, Folder *current)
    {
        while (current != nullptr)
        {
            // Use IsExitDir to search within current folder
            Folder *found = IsExitDir(dir, current);
            if (found != nullptr)
            {
                return found;
            }

            // Move up one level
            current = current->Parent;
        }

        // Not found in current folder or ancestor folders
        return nullptr;
    }
    Folder *IsExitDir(string Name, Folder *current)
    {
        for (auto &subfolder : current->SubFolders)
        {
            if (subfolder->name == Name)
            {
                return subfolder;
            }
        }
        return nullptr;
    }
    bool CheckFile(string name, string exe)
    {
        list<File *>::iterator it;
        for (it = SubFiles.begin(); it != SubFiles.end(); it++)
        {
            if ((*it)->Extension == exe && (*it)->name == name)
            {
                return true;
            }
        }
        return false;
    }
    void ChangeExtension(string prviousexe, string newexe)
    {
        list<File *>::iterator it;
        for (it = SubFiles.begin(); it != SubFiles.end(); it++)
        {
            if ((*it)->Extension == prviousexe)
            {
                (*it)->Extension = newexe;
            }
        }
    }
    void RenameFile(string oldName, string newName, string prevexe, string newexe)
    {
        list<File *>::iterator it;
        for (it = SubFiles.begin(); it != SubFiles.end(); it++)
        {
            if ((*it)->name == oldName && (*it)->Extension == prevexe)
            {
                (*it)->name = newName;
                (*it)->Extension = newexe;
            }
        }
    }
    void Format(Folder *current)
    {
        current->SubFiles.clear();
        current->SubFolders.clear();
    }
    void printTreeHelper(Folder *folder, int level, bool isLastChild)
    {
        if (folder == nullptr)
        {
            return;
        }

        // Print the current folder
        for (int i = 0; i < level - 1; ++i)
        {
            cout << "  "; // Adjust the indentation level
            cout << (i == level - 2 ? "|_______" : "     ");
        }

        if (level > 0)
        {
            if (isLastChild)
            {
                cout << "`_______";
            }
            else
            {
                cout << "|_______";
            }
        }
        cout << folder->name << endl;

        // Print files in the current folder
        for (const auto &file : folder->SubFiles)
        {
            for (int i = 0; i < level; ++i)
            {
                cout << "  "; // Adjust the indentation level for files
                cout << (i == level - 1 ? "|_______" : "     ");
            }
            cout << file->name <<file->Extension << endl;
        }

        // Recursively print subfolders
        for (const auto &subfolder : folder->SubFolders)
        {
            printTreeHelper(subfolder, level + 1, &subfolder == &folder->SubFolders.back());
        }
    }

    void PrintTree(Folder *root)
    {
        cout << "Directory Tree:" << endl;
        printTreeHelper(root, 0, true);
    }

    void Help()
    {
        cout << "mkdir\tMakes a new directory in current directory" << endl;
        cout << "cd\tChanges the current directory" << endl;
        cout << "cd.\tChanges current directory to its parent directory" << endl;
        cout << "cd..\tChanges current directory to its previous directory" << endl;
        cout << "cd\\\tChange the directory to its root directory" << endl;
        cout << "create\tCreate file and allow user to enter content" << endl;
        cout << "dir\tDisplays a list of files and subdirectories in a directory" << endl;
        cout << "attrib\tDisplays file attributes" << endl;
        cout << "copy\tCopies one file in the current directory to another location" << endl;
        cout << "del\tDelete a file whose name is provided in input" << endl;
        cout << "quit\tQuits the program" << endl;
        cout << "find\tSearches for a file in your current virtual directory whose name is provided as input" << endl;
        cout << "format\tFormats the current virtual directory i.e. empties the current directory and all subdirectories" << endl;
    }
};
