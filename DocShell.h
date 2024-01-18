#pragma once
#include "Folder.h"
#include <iostream>
using namespace std;
class Docshell
{
public:
  Folder *CurrentFolder;
  Folder *Root;
  string usercommand = "";
  Docshell()
  {
    Root = CurrentFolder = new Folder("V", nullptr, "V:");
  }
  void color1(int color1)
  {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
  }

  void gotoxy(int x, int y)
  {
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
  }
  void printName()
  {
    system("cls");
    char ch1 = 186;
    color1(6);
    gotoxy(55, 1);
    cout << ch1 << ch1 << "Muhammad Awais Ashraf" << ch1 << ch1 << "2022-CS-186" << ch1 << ch1 << "DSA BY Sir Faraz" << ch1 << ch1 << endl;
    color1(7);
  }
  void run()
  {
    while (1)
    {
      printName();
      cout << CurrentFolder->path << ">";
      getline(cin, usercommand);
      if (usercommand == "exit" || usercommand == "EXIT")
      {
        break;
      }
      else if (usercommand == "cls")
      {
        system("cls");
      }
      else if (usercommand.substr(0, 3) == "dir")
      {
        CurrentFolder->PrintDir();
        getch();
      }
      else if (usercommand == "CD." || usercommand == "cd." || usercommand == "pwd")
      {
        cout << CurrentFolder->name;
        getch();
      }

      else if (usercommand == "CD.." || usercommand == "cd..")
      {
        if (CurrentFolder->Parent != nullptr)
        {
          CurrentFolder = CurrentFolder->Parent;
        }
      }
      else if (usercommand.substr(0, 3) == "CD\\" || usercommand.substr(0, 3) == "cd\\")
      {
        CurrentFolder = Root;
      }
      else if (usercommand.substr(0, 5) == "MKDIR" || usercommand.substr(0, 5) == "mkdir")
      {
        string newFolderName = usercommand.substr(6);
        if (!newFolderName.empty() && newFolderName.find_first_not_of(' ') != string::npos)
          createVirtualDirectory(newFolderName);
        else
        {
          cout << "Invalid folder name. Please provide a valid folder name after MKDIR";
          getch();
        }
      }
      else if ((usercommand.substr(0, 5) == "RMDIR" || usercommand.substr(0, 5) == "rmdir") && (usercommand.length() > 5))
      {
        string FolderName = usercommand.substr(6);
        Folder *RemoveAbleFoldr = CurrentFolder->IsExitDir(FolderName);
        if (RemoveAbleFoldr != nullptr)
        {
          CurrentFolder->RemoveDir(RemoveAbleFoldr);
        }
        else
        {
          cout << "Folder not exits:";
          getch();
        }
      }
      else if ((usercommand.substr(0, 2) == "CD" || usercommand.substr(0, 2) == "cd") && (usercommand.length() > 2))
      {
        string FolderName = usercommand.substr(3);
        Folder *newFolder = CurrentFolder->IsExitDir(FolderName);
        if (newFolder != nullptr)
        {
          CurrentFolder = newFolder;
        }
        else
        {
          cout << "Folder not Exits:";
          getch();
        }
      }
      else if ((usercommand.substr(0, 6) == "Create" || usercommand.substr(0, 6) == "create"))
      {
        if (usercommand.length() >= 7)
        {
          int dotPosition = finddot(usercommand.substr(7));
          if (dotPosition != -1)
          {
            string filename = usercommand.substr(7);
            string ActualName = Cutname(filename, dotPosition);
            string fileExtension = filename.substr(dotPosition);
            if (CheckValidEXtension(fileExtension))
            {
              CreateFile(ActualName, fileExtension);
            }
            else
            {
              cout << "invalid extension..Some valid Extensions are txt,cpp,cs etc";
              getch();
            }
          }
          else
          {
            cout << "Please Enter a Valid File Name with vaild Extension";
            getch();
          }
        }
        else
        {
          cout << "Please Enter File Name." << endl;
          getch();
        }
      }
      else if (usercommand.substr(0, 3) == "Del" || usercommand.substr(0, 3) == "del")
      {
        int dotPosition = finddot(usercommand.substr(4));
        if (dotPosition != -1)
        {
          string filename = usercommand.substr(4);
          string ActualName = Cutname(filename, dotPosition);
          string fileExtension = filename.substr(dotPosition);
          File *RemoveAbleFile = CurrentFolder->IsExitFile(ActualName, fileExtension);
          if (RemoveAbleFile != nullptr)
          {
            CurrentFolder->RemoveFile(RemoveAbleFile);
          }
          else
          {
            cout << "File not Exits:";
            getch();
          }
        }
        else
        {
          cout << "File not Exits.Please Enter Extension as well";
          getch();
        }
      }
      else if ((usercommand.substr(0, 4) == "Find" || usercommand.substr(0, 4) == "find") && usercommand.length() >= 5)
      {
        int dotPosition = finddot(usercommand.substr(5));
        if (dotPosition != -1)
        {
          string filename = usercommand.substr(5);
          string fileExtension = filename.substr(dotPosition);
          string ActualName = Cutname(filename, dotPosition);
          File *File = CurrentFolder->IsExitFile(ActualName, fileExtension);
          if (File != nullptr)
          {
            cout << File->name << File->Extension;
            getch();
          }
          else
          {
            cout << "File not Exits:";
            getch();
          }
        }
        else
        {
          cout << "Invalid Name.Enter Extension also:";
          getch();
        }
      }
      else if (usercommand == "ver" || usercommand == "Ver")
      {
        color1(2);
        cout << "DOCSHELL Version 1.0...Stay Connected For Update:";
        color1(7);
        getch();
      }
      else if ((usercommand == "convert" || usercommand == "Convert"))
      {
        string previousexe;
        cout << "Enter Name of File Extension To Change Type:";
        cin >> previousexe;
        if (previousexe.length() > 0)
        {
          if (CurrentFolder->CheckFileEXE(previousexe))
          {
            string newexe;
            cout << "Enter New Type:";
            cin >> newexe;
            if (!newexe.empty() && CheckValidEXtension(newexe))
            {
              CurrentFolder->ChangeExtension(previousexe, newexe);
            }
            else
            {
              cout << "invalid extension..Some valid Extensions are txt,cpp,cs,exe etc";
              getch();
            }
          }
          else
          {
            cout << "No File With Such Extension in your Current Dir:";
            getch();
          }
        }
        else
        {
          cout << "Invalid Format:";
          getch();
        }
      }
      else if (usercommand == "Format" || usercommand == "format")
      {
        CurrentFolder->Format(CurrentFolder);
      }
      else if (usercommand == "rename" || usercommand == "Rename")
      {
        string oldName;
        cout << "Enter the current name of the file to rename: ";
        cin >> oldName;
        int dotpostion = finddot(oldName);
        if (oldName.length() > 0 && dotpostion != -1)
        {
          string PrevExtension = oldName.substr(dotpostion);
          string OnlyPrevname = Cutname(oldName, dotpostion);
          if (CurrentFolder->CheckFile(OnlyPrevname, PrevExtension))
          {
            string newName;
            cout << "Enter the new name for the file: ";
            cin >> newName;
            int dotpostion = finddot(newName);
            if (!newName.empty() && dotpostion != -1)
            {
              string NewExtension = newName.substr(dotpostion);
              if (CheckValidEXtension(NewExtension))
              {
                string OnlyNewname = Cutname(newName, dotpostion);
                CurrentFolder->RenameFile(OnlyPrevname, OnlyNewname, PrevExtension, NewExtension);
                cout << "File renamed successfully." << endl;
                getch();
              }
              else
              {
                cout << "Invalid new Exe. Please enter a  valid extension like .exe,.cpp .txt  etc.";
                getch();
              }
            }
            else
            {
              cout << "Invalid new name. Please enter a valid name with valid extension like .exe,.cpp .txt  etc." << endl;
              getch();
            }
          }
          else
          {
            cout << "No file with such name in your current directory." << endl;
            getch();
          }
        }
        else
        {
          cout << "Invalid format. Please enter a valid name and extension" << endl;
        }
      }
      else if(usercommand=="tree")
      {
        CurrentFolder->PrintTree(Root);
        getch();
      }
      else if (usercommand=="help")
      {
       CurrentFolder->Help();
       getch();
      }
      else if (usercommand == "copy")
      {
        string file;
        cout << "File to Copy:";
        cin >> file;
        int dotpostion = finddot(file);
        if (file.length() > 0 && dotpostion != -1)
        {
          string fileExtension = file.substr(dotpostion);
          string filename = Cutname(file, dotpostion);
          if (CurrentFolder->CheckFile(filename, fileExtension))
          {
            string newdirector;
            cout << "Enter Directory where you want to copy file:";
            cin >> newdirector;
            Folder *CopiedDirectory = Location(newdirector);
            if (CopiedDirectory != nullptr)
            {
              CreateFile(filename, fileExtension);
            }
            else
            {
              cout << "No directory with such name in your docshell." << endl;
              getch();
            }
          }
          else
          {
            cout << "No file with such name in your current directory." << endl;
            getch();
          }
        }
        else
        {
          cout << "Invalid format. Please enter a valid name and extension" << endl;
          getch();
        }
      }
      // else
      // {
      //   PrintCommandNotFound(usercommand);
      // }
    }
  }
  void createVirtualDirectory(string foldername)
  {
    Folder *newfolder = new Folder(foldername, CurrentFolder, CurrentFolder->path + "\\" + foldername);
    CurrentFolder->AddFolder(newfolder);
  }
  void CreateFile(string filename, string exe)
  {
    File *file = new File(filename, exe);
    CurrentFolder->AddFile(file);
  }
  int finddot(string name)
  {
    int index = -1;
    for (int i = 0; i < name.length(); i++)
    {
      if (name[i] == '.')
      {
        index = i;
      }
    }
    return index;
  }
  bool CheckValidEXtension(string valid)
  {
    if (valid == ".cs" || valid == ".cpp" || valid == ".txt" || valid == ".exe")
    {
      return true;
    }
    return false;
  }
  string Cutname(string name, int lastindex)
  {
    string filename = "";
    for (int i = 0; i < lastindex; i++)
    {
      filename += name[i];
    }

    return filename;
  }
  void PrintCommandNotFound(string command)
  {
    cout << "'" << command << "' is not recognized as an internal or external command,\n";
    cout << "operable program or batch file." << endl;
    getch();
  }
  // Folder *Location(const string &path, Folder *root)
  // {
  //   size_t pos = 0;
  //   Folder *current = root;

  //   while ((pos = path.find('\\')) != string::npos)
  //   {
  //     string component = path.substr(0, pos);
  //     Folder *next = CurrentFolder->CheckDirectory(component, current);
  //     if (next == nullptr)
  //     {
  //       cout << "Invalid path: " << component << " not found." << endl;
  //       return nullptr;
  //     }
  //     current = next;
  //     // path.erase(0, pos + 1);
  //   }

  //   Folder *lastComponent = CurrentFolder->CheckDirectory(path, current);
  //   if (lastComponent == nullptr)
  //   {
  //     cout << "Invalid path: " << path << " not found." << endl;
  //     return nullptr;
  //   }

  //   return lastComponent;
  // }
  Folder *Location(string name)
  {
    Folder *current = nullptr; // Assuming you have a "root" folder somewhere

    // Iterate through path components separated by '/'
    size_t pos = 0;
    while ((pos = name.find('/', pos)) != string::npos)
    {
      string dir = name.substr(0, pos);

      // Check if directory exists in current folder
      current = CurrentFolder->CheckDirectory(dir, current);
      if (current == nullptr)
      {
        return nullptr; // Not found
      }

      pos += 1; // Move to next dir after '/'
    }

    // Check final directory name at the end
    string lastDir = name.substr(pos);
    return CurrentFolder->IsExitDir(lastDir, current);
  }
};