#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> pastedata;
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
void Hide_Cursor()
{
  CONSOLE_CURSOR_INFO cursor_info = {1, 0};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void Page()
{
  color1(2);
  gotoxy(50, 1);
  cout << "  __  __   _           _     ______                        _ ";
  gotoxy(50, 2);
  cout << " |  \\/  | (_)         (_)   |  ____|                      | |";
  gotoxy(50, 3);
  cout << " | \\  / |  _   _ __    _    | |__    __  __   ___    ___  | |";
  gotoxy(50, 4);
  cout << " | |\\/| | | | | '_ \\  | |   |  __|   \\ \\/ /  / __|  / _ \\ | |";
  gotoxy(50, 5);
  cout << " | |  | | | | | | | | | |   | |____   >  <  | (__  |  __/ | |";
  gotoxy(50, 6);
  cout << " |_|  |_| |_| |_| |_| |_|   |______| /_/\\_\\  \\___|  \\___| |_|";
  color1(7);
}
void menu(int currentmenu)
{
  Page();
  string menu[4] = {
      "New Sheet",
      "Previous Sheet",
      "Help",
      "Exit"};
  color1(2);
  gotoxy(72, 9);
  cout << "|| Main Menu ||" << endl;
  color1(7);
  for (int i = 0; i < 4; i++)
  {
    if (i == currentmenu)
    {
      color1(6);
    }
    gotoxy(71, 12 + i);
    cout << "--> " << menu[i];
    color1(7);
  }
}
void help()
{
  system("cls");
  Page();
  color1(8);
  gotoxy(73 - 13, 8 + 1);
  cout << "Press A: Move Current Cell Left";
  gotoxy(73 - 13, 9 + 1);
  cout << "Press D: Move Current Cell Right";
  gotoxy(73 - 13, 10 + 1);
  cout << "Press W: Move Current Cell Up";
  gotoxy(73 - 13, 11 + 1);
  cout << "Press S: Move Current Cell Down";
  gotoxy(73 - 13, 12 + 1);
  cout << "Press U: Insert Column Above Current Cell";
  gotoxy(73 - 13, 13 + 1);
  cout << "Press B: Insert Column Below Current Cell";
  gotoxy(73 - 13, 14 + 1);
  cout << "Press V: Insert Value in Current Cell";
  gotoxy(73 - 13, 15 + 1);
  cout << "Press L: Insert Column to the Left of Current Cell";
  gotoxy(73 - 13, 16 + 1);
  cout << "Press R: Insert Cell by Right Shifting";
  gotoxy(73 - 13, 17 + 1);
  cout << "Press E: Insert Cell by Down Shifting";
  gotoxy(73 - 13, 18 + 1);
  cout << "Press J: Delete Current Row";
  gotoxy(73 - 13, 19 + 1);
  cout << "Press K: Delete Current Column";
  gotoxy(73 - 13, 20 + 1);
  cout << "Press C: Clear Current Row";
  gotoxy(73 - 13, 21 + 1);
  cout << "Press X: Clear Current Column";
  gotoxy(73 - 13, 22 + 1);
  cout << "Press Q: Calculate Range Sum";
  gotoxy(73 - 13, 23 + 1);
  cout << "Press G: Calculate Range Average";
  gotoxy(73 - 13, 24 + 1);
  cout << "Press O: Count Cells";
  gotoxy(73 - 13, 25 + 1);
  cout << "Press M: Find Maximum Value";
  gotoxy(73 - 13, 26 + 1);
  cout << "Press I: Find Minimum Value";
  gotoxy(73 - 13, 27 + 1);
  cout << "Press Y: Copy";
  gotoxy(73 - 13, 28 + 1);
  cout << "Press T: Cut";
  gotoxy(73 - 13, 29 + 1);
  cout << "Press P: Paste";
  gotoxy(73 - 13, 30 + 1);
  cout << "Press Escape: Exit";
  gotoxy(73 - 13, 31 + 1);
  cout << "Press Tab: Save Sheet";
  color1(7);
  getch();
}
class Cell
{
public:
  string value;
  Cell *up;
  Cell *down;
  Cell *left;
  Cell *right;
  Cell(string val)
  {
    value = val;
    up = nullptr;
    down = nullptr;
    left = nullptr;
    right = nullptr;
  }
};

class MiniExcel
{
public:
  Cell *head = nullptr;
  Cell *current = nullptr;
  int CountRows = 0;
  int CountCols = 0;
  const int cellWidth = 11;
  const int cellHeight = 5;
  vector<int> copy;
  MiniExcel(int choice)
  {
    if (choice == 1)
    {
      loadfromfile();
    }
    else
    {
      start();
    }
  }
  void start()
  {
    Cell *temp;
    for (int row = 0; row < 5; row++)
    {

      for (int col = 0; col < 5; col++)
      {
        Cell *newcell = new Cell(" ");
        if (row == 0)
        {
          if (head == nullptr)
          {
            head = newcell;
            current = newcell;
          }
          else
          {
            current->right = newcell;
            newcell->left = current;
            current = newcell;
          }
        }
        else
        {

          temp->down = newcell;
          newcell->up = temp;
          if (col != 0)
          {
            current->right = newcell;
            newcell->left = current;
          }
          current = newcell;
          temp = temp->right;
        }
      }

      while (current->left != nullptr) // loop for retreive current to 0 place
      {
        current = current->left;
      }
      temp = current;
    }

    current = head;
    CountCols = 5;
    CountRows = 5;
  }

  void printCorners(char ch)
  {
    cout << ch;
  }

  void horizontalBorders(int width, char ch)
  {
    for (int i = 1; i < width - 1; ++i)
    {
      cout << ch;
    }
  }

  void printCell(Cell *cell, int x, int y)
  {

    const char horizontalBorder = 205;
    const char verticalBorder = 186;

    gotoxy(x, y);
    printCorners(201); // top left
    horizontalBorders(cellWidth, 205);
    printCorners(187); // top right
    cout << endl;

    // Print cell value and vertical borders
    for (int i = 0; i < cellHeight - 2; ++i)
    {
      gotoxy(x, y + i + 1);
      cout << verticalBorder;
      for (int j = 1; j < cellWidth - 1; ++j)
      {
        if (i == (cellHeight - 2) / 2)
        {
          int valueStart = (cellWidth - cell->value.length()) / 2;
          int valueEnd = valueStart + cell->value.length();
          if (j >= valueStart && j < valueEnd)
          {
            std::cout << cell->value[j - valueStart];
          }
          else
          {
            cout << " ";
          }
        }
        else
        {
          cout << " ";
        }
      }
      cout << verticalBorder << endl;
    }

    gotoxy(x, y + cellHeight - 1);
    printCorners(200); // bottom left
    horizontalBorders(cellWidth, horizontalBorder);
    printCorners(188); // bottom right
    cout << endl;
  }

  void print5by5()
  {
    int x = 0;
    int y = 0;
    for (Cell *row = head; row != nullptr; row = row->down, y++)
    {
      for (Cell *col = row; col != nullptr; col = col->right, x++)
      {
        if (col == current)
        {
          color1(4);
        }
        else
        {
          color1(2);
        }
        printCell(col, x * cellWidth, y * cellHeight);
      }

      x = 0;
    }
    color1(7);
  }

  string CurrentHeadValue()
  {
    if (head != nullptr)
      return head->value;
  }
  void SetHeadVal(string val)
  {
    head->value = val;
  }
  string CurrentCellValue()
  {
    if (current != nullptr)
      return current->value;
  }
  void MoveCurrentRight()
  {
    if (current->right != nullptr)
      current = current->right;
  }
  void MoveCurrentLeft()
  {
    if (current->left != nullptr)
      current = current->left;
  }
  void MoveCurrentUp()
  {

    if (current->up != nullptr)
      current = current->up;
  }

  void MoveCurrentDown()
  {
    if (current->down != nullptr)
      current = current->down;
  }
  void SetCurrentValue(string val)
  {
    current->value = val;
  }
  void InsertRowAboveCurrentCell()
  {
    Cell *oldcurrent = current; // to store current first location
    while (current->left != nullptr)
    {
      current = current->left; // try to move currentcell's starting cell
    }

    Cell *temp = current; // inserting new row when there is no row above currentcell
    if (current->up == nullptr)
    {
      for (; current != nullptr; current = current->right)
      {
        Cell *newcell = new Cell(" ");
        current->up = newcell;
        newcell->down = current;
        if (temp != current)
        {
          temp->right = newcell;
          newcell->left = temp;
          temp = temp->right;
        }
        else
        {
          temp = newcell;
        }
      }
      while (temp->left != nullptr) // try to move to temp to start as we have to change head
      {                             // in this case
        temp = temp->left;
      }
      head = temp;
    }
    else                          // case when current is between two rows and we have to insert row in
    {                             // middle
      Cell *tempup = current->up; // to store current top node
      for (; current != nullptr; current = current->right)
      {
        Cell *newcell = new Cell(" ");
        current->up = newcell;
        newcell->down = current;
        if (temp != current)
        {
          temp->right = newcell;
          newcell->left = temp;
          temp = temp->right;
          tempup = tempup->right;
        }
        else
        {
          temp = newcell;
        }
        tempup->down = temp;
        temp->up = tempup;
      }
    }
    current = oldcurrent; // move current to previous location
    CountRows++;
  }

  void InsertRowBelowCurrentCell()
  {
    Cell *oldcurrent = current; // to store current first location
    while (current->left != nullptr)
    {
      current = current->left; // try to move currentcell's to starting cell
    }
    Cell *temp = current; // inserting new row when there is no row above currentcell
    if (current->down == nullptr)
    {
      for (; current != nullptr; current = current->right)
      {
        Cell *newcell = new Cell(" ");
        current->down = newcell;
        newcell->up = current;
        if (temp != current)
        {
          temp->right = newcell;
          newcell->left = temp;
          temp = temp->right;
        }
        else
        {
          temp = newcell;
        }
      }
    }
    else                              // case when current is between two rows and we have to insert row in
    {                                 // middle
      Cell *tempdown = current->down; // to store current down node
      for (; current != nullptr; current = current->right)
      {
        Cell *newcell = new Cell(" ");
        current->down = newcell;
        newcell->up = current;
        if (temp != current)
        {
          temp->right = newcell;
          newcell->left = temp;
          temp = temp->right;
          tempdown = tempdown->right;
        }
        else
        {
          temp = newcell;
        }
        tempdown->up = temp;
        temp->down = tempdown;
      }
    }
    current = oldcurrent; // move current to previous location
    CountRows++;
  }
  void insertColumnRightToCurrentCell()
  {
    Cell *oldcurrent = current; // to store current first location

    while (current->up != nullptr)
    {
      current = current->up; // try to move currentcell's to starting cell
    }

    Cell *temp = current; // inserting new row when there is no col right currentcell
    if (current->right == nullptr)
    {
      for (; current != nullptr; current = current->down)
      {
        Cell *newcell = new Cell(" ");
        current->right = newcell;
        newcell->left = current;
        if (temp != current)
        {
          temp->down = newcell;
          newcell->up = temp;
          temp = temp->down;
        }
        else
        {
          temp = newcell;
        }
      }
    }
    else                                // case when current is between two cok and we have to insert col in
    {                                   // middle
      Cell *tempright = current->right; // to store current right node
      for (; current != nullptr; current = current->down)
      {
        Cell *newcell = new Cell(" ");
        current->right = newcell;
        newcell->left = current;
        if (temp != current)
        {
          temp->down = newcell;
          newcell->up = temp;
          temp = temp->down;
          tempright = tempright->down;
        }
        else
        {
          temp = newcell;
        }
        temp->right = tempright;
        tempright->left = temp;
      }
    }
    current = oldcurrent;
    CountCols++;
  }
  void InsertColLeftToCurrentCell()
  {
    Cell *oldcurrent = current; // to store current first location
    while (current->up != nullptr)
    {
      current = current->up; // try to move currentcell's to starting cell
    }
    Cell *temp = current; // inserting new row when there is no col right currentcell
    if (current->left == nullptr)
    {
      for (; current != nullptr; current = current->down)
      {
        Cell *newcell = new Cell(" ");
        current->left = newcell;
        newcell->right = current;
        if (temp != current)
        {
          temp->down = newcell;
          newcell->up = temp;
          temp = temp->down;
        }
        else
        {
          temp = newcell;
        }
      }
      while (temp->up != nullptr) // try to move to temp to start as we have to change head
      {                           // in this case
        temp = temp->up;
      }
      head = temp;
    }
    else                              // case when current is between two cok and we have to insert col in
    {                                 // middle
      Cell *templeft = current->left; // to store current left node
      for (; current != nullptr; current = current->down)
      {
        Cell *newcell = new Cell(" ");
        current->left = newcell;
        newcell->right = current;
        if (temp != current)
        {
          temp->down = newcell;
          newcell->up = temp;
          temp = temp->down;
          templeft = templeft->down;
        }
        else
        {
          temp = newcell;
        }
        templeft->right = temp;
        temp->left = templeft;
      }
    }
    current = oldcurrent;
    CountCols++;
  }
  void InsertCellByRightShift()
  {
    Cell *temp = current;
    while (current->right != nullptr)
    {
      current = current->right;
    }
    insertColumnRightToCurrentCell();
    current = current->right;
    while (current != temp)
    {
      current->value = current->left->value;
      current = current->left;
    }
    current->value = "   ";
  }
  void DeleteCellByLeftShift()
  {
    Cell *temp = current;
    temp->value = "    ";
    while (temp->right != nullptr)
    {
      temp->value = temp->right->value;
      temp = temp->right;
    }
    temp->value = "    ";
  }

  void InsertCellByDownShift()
  {
    Cell *temp = current;
    while (current->down != nullptr)
    {
      current = current->down;
    }
    InsertRowBelowCurrentCell();
    current = current->down;
    while (current != temp)
    {
      current->value = current->up->value;
      current = current->up;
    }
    current->value = "   ";
  }
  void deleteRow()
  {
    while (current->left != nullptr)
    {
      current = current->left; // try to move currentcell's to starting cell
    }
    if (current->up == nullptr) // delete firstRow
    {
      head = current->down;
      Cell *temp;
      while (current != nullptr) // simply you can change head but loop for previois head down null
      {
        temp = current->down;
        temp->up = nullptr;
        current = current->right;
      }
    }
    else if (current->down == nullptr) // delete lastRow
    {
      Cell *tempup; // current upper node      2 delete 1 and 3 link
      while (current != nullptr)
      {
        tempup = current->up; // current upper node      2 delete 1 and 3 link
        tempup->down = nullptr;
        current = current->right;
      }
    }
    else
    {
      Cell *tempup;   // current upper node      2 delete 1 and 3 link
      Cell *tempdown; // current down node
      while (current != nullptr)
      {
        tempup = current->up;     // current upper node      2 delete 1 and 3 link
        tempdown = current->down; // current down node
        tempup->down = tempdown;
        tempdown->up = tempup;
        current = current->right;
      }
    }
    current = head;
    CountRows--;
  }
  void deleteCol()
  {
    while (current->up != nullptr)
    {
      current = current->up; // try to move currentcell's to starting cell
    }
    if (current->left == nullptr) // delete firstCol
    {
      head = current->right;
      Cell *temp;
      while (current->down != nullptr)
      {
        temp = current->right;
        temp->left = nullptr;
        current = current->down;
      }
    }
    else if (current->right == nullptr) // delete lastCol
    {
      Cell *templeft;
      while (current != nullptr)
      {
        templeft = current->left;
        templeft->right = nullptr;
        current = current->down;
      }
    }
    else
    {
      Cell *templeft;
      Cell *tempright;
      while (current != nullptr)
      {
        templeft = current->left;   // current left node      2 delete 1 and 3 link
        tempright = current->right; // current right node
        templeft->right = tempright;
        tempright->left = templeft;
        current = current->down;
      }
    }
    current = head;
  }
  void ClearRow()
  {
    Cell *oldcurrent = current;
    while (current->left != nullptr)
    {
      current = current->left; // try to move currentcell's to starting cell
    }
    while (current != nullptr)
    {
      current->value = "     ";
      current = current->right;
    }
    current = oldcurrent;
    CountRows--;
  }
  void ClearCol()
  {
    Cell *oldcurrent = current;
    while (current->up != nullptr)
    {
      current = current->up; // try to move currentcell's to starting cell
    }
    while (current != nullptr)
    {
      current->value = "     ";
      current = current->down;
    }
    current = oldcurrent;
  }
  int RangeSum(int start, int end)
  {
    int sum = 0;
    Cell *startingcell = nullptr;
    Cell *endingcell = nullptr;
    if (start < end)
    {
      startingcell = mark(start);
      endingcell = mark(end);
    }
    else if (start == end)
    {
      Cell *cell = mark(start);
      sum = ConvertStringToInt(cell->value);
      return sum;
    }
    else
    {
      startingcell = mark(end);
      endingcell = mark(start);
    }
    if (startingcell == nullptr || endingcell == nullptr)
    {
      cout << "invalid range:";
      return -1;
    }
    else
    {
      while (startingcell != endingcell)
      {
        int value = ConvertStringToInt(startingcell->value);
        sum += value;
        if (startingcell->right != nullptr)
        {
          startingcell = startingcell->right;
        }
        else
        {
          while (startingcell->left != nullptr)
          {
            startingcell = startingcell->left;
          }
          startingcell = startingcell->down;
        }
      }
      sum += ConvertStringToInt(endingcell->value);
    }
    return sum;
  }
  int RangeAvg(int start, int end)
  {
    int avgsum = 0;
    int count = 0;
    Cell *startingcell = nullptr;
    Cell *endingcell = nullptr;
    if (start < end)
    {
      startingcell = mark(start);
      endingcell = mark(end);
    }
    else if (start == end)
    {
      Cell *cell = mark(start);
      avgsum = ConvertStringToInt(cell->value);
      return avgsum;
    }
    else
    {
      startingcell = mark(end);
      endingcell = mark(start);
    }
    if (startingcell == nullptr || endingcell == nullptr)
    {
      cout << "invalid range:";
      return -1;
    }
    else
    {
      while (startingcell != endingcell)
      {
        int value = ConvertStringToInt(startingcell->value);
        avgsum += value;
        count++;
        if (startingcell->right != nullptr)
        {
          startingcell = startingcell->right;
        }
        else
        {
          while (startingcell->left != nullptr)
          {
            startingcell = startingcell->left;
          }
          startingcell = startingcell->down;
        }
      }
      avgsum += ConvertStringToInt(endingcell->value);
      count++;
    }
    return avgsum / count;
  }
  int Count(int start, int end)
  {
    int count = 0;
    Cell *startingcell = nullptr;
    Cell *endingcell = nullptr;
    if (start < end)
    {
      startingcell = mark(start);
      endingcell = mark(end);
    }
    else if (start == end)
    {
      return 1;
    }
    else
    {
      startingcell = mark(end);
      endingcell = mark(start);
    }
    if (startingcell == nullptr || endingcell == nullptr)
    {
      cout << "invalid range:";
      return -1;
    }
    else
    {
      while (startingcell != endingcell)
      {
        count++;
        if (startingcell->right != nullptr)
        {
          startingcell = startingcell->right;
        }
        else
        {
          while (startingcell->left != nullptr)
          {
            startingcell = startingcell->left;
          }
          startingcell = startingcell->down;
        }
      }
      count++;
    }
    return count;
  }
  Cell *mark(int value)
  {
    int row = value / 10;
    int col = value % 10; // pass 02 to 11 means o row 2 cell to 1 row 1 cell
    Cell *temp = head;
    for (int i = 0; i < row; i++)
    {
      temp = temp->down;
    }
    for (int i = 0; i < col; i++)
    {
      temp = temp->right;
    }
    return temp;
  }
  int Max(int start, int end)
  {
    int max = -32000;
    Cell *startingcell = nullptr;
    Cell *endingcell = nullptr;
    if (start < end)
    {
      startingcell = mark(start);
      endingcell = mark(end);
    }
    else if (start == end)
    {
      Cell *cell = mark(start);
      max = ConvertStringToInt(cell->value);
      return max;
    }
    else
    {
      startingcell = mark(end);
      endingcell = mark(start);
    }
    if (startingcell == nullptr || endingcell == nullptr)
    {
      cout << "invalid range:";
      return -1;
    }
    else
    {
      while (startingcell != endingcell)
      {
        int value = ConvertStringToInt(startingcell->value);
        if (value > max)
        {
          max = value;
        }
        if (startingcell->right != nullptr)
        {
          startingcell = startingcell->right;
        }
        else
        {
          while (startingcell->left != nullptr)
          {
            startingcell = startingcell->left;
          }
          startingcell = startingcell->down;
        }
      }
      int value = ConvertStringToInt(startingcell->value);
      if (value > max)
      {
        max = value;
      }
    }
    return max;
  }
  int Min(int start, int end)
  {
    int min = 32000;
    Cell *startingcell = nullptr;
    Cell *endingcell = nullptr;
    if (start < end)
    {
      startingcell = mark(start);
      endingcell = mark(end);
    }
    else if (start == end)
    {
      Cell *cell = mark(start);
      min = ConvertStringToInt(cell->value);
      return min;
    }
    else
    {
      startingcell = mark(end);
      endingcell = mark(start);
    }
    if (startingcell == nullptr || endingcell == nullptr)
    {
      cout << "invalid range:";
      return -1;
    }
    else
    {
      while (startingcell != endingcell)
      {
        int value = ConvertStringToInt(startingcell->value);
        if (value < min)
        {
          min = value;
        }
        if (startingcell->right != nullptr)
        {
          startingcell = startingcell->right;
        }
        else
        {
          while (startingcell->left != nullptr)
          {
            startingcell = startingcell->left;
          }
          startingcell = startingcell->down;
        }
      }
      int value = ConvertStringToInt(startingcell->value);
      if (value < min)
      {
        min = value;
      }
    }
    return min;
  }
  void Copy(int start, int end)
  {
    copy.clear();

    Cell *startingcell = nullptr;
    Cell *endingcell = nullptr;
    if (start < end)
    {
      startingcell = mark(start);
      endingcell = mark(end);
    }
    else if (start == end)
    {
      Cell *cell = mark(start);
      int value = ConvertStringToInt(cell->value);
      copy.push_back(value);
    }
    else
    {
      startingcell = mark(end);
      endingcell = mark(start);
    }
    if (startingcell == nullptr || endingcell == nullptr)
    {
      cout << "invalid range:";
      //   return -1;
    }
    else
    {
      while (startingcell != endingcell)
      {
        int value = ConvertStringToInt(startingcell->value);
        copy.push_back(value);
        if (startingcell->right != nullptr)
        {
          startingcell = startingcell->right;
        }
        else
        {
          while (startingcell->left != nullptr)
          {
            startingcell = startingcell->left;
          }
          startingcell = startingcell->down;
        }
      }
      int value = ConvertStringToInt(endingcell->value);
      copy.push_back(value);
    }
  }
  void Cut(int start, int end)
  {
    Cell *startingcell = nullptr;
    Cell *endingcell = nullptr;
    if (start < end)
    {
      startingcell = mark(start);
      endingcell = mark(end);
    }
    else if (start == end)
    {
      Cell *cell = mark(start);
      int value = ConvertStringToInt(cell->value);
      cell->value = "   ";
      copy.push_back(value);
    }
    else
    {
      startingcell = mark(end);
      endingcell = mark(start);
    }
    if (startingcell == nullptr || endingcell == nullptr)
    {
      cout << "invalid range:";
      //   return -1;
    }
    else
    {
      while (startingcell != endingcell)
      {
        int value = ConvertStringToInt(startingcell->value);
        startingcell->value = "   ";
        copy.push_back(value);
        if (startingcell->right != nullptr)
        {
          startingcell = startingcell->right;
        }
        else
        {
          while (startingcell->left != nullptr)
          {
            startingcell = startingcell->left;
          }
          startingcell = startingcell->down;
        }
      }
      int value = ConvertStringToInt(endingcell->value);
      endingcell->value = "   ";
      copy.push_back(value);
    }
  }
  void printcopycutdata()
  {
    cout << "Copied Values:" << endl;
    for (int value : copy)
    {
      cout << value << " ";
    }
  }
  void paste()
  {
    int n = copy.size();
    Cell *cell = current;
    for (int i = 0; i < n; i++)
    {
      if (cell->right == nullptr)
      {
        insertColumnRightToCurrentCell();
      }
      cell->left->value = to_string(copy[i]);
      cell = cell->right;
    }
  }
  int ConvertStringToInt(string str)
  {
    // Check if the string is empty or contains only spaces.
    if (str.empty() || str.find_first_not_of(' ') == string::npos)
    {
      return 0;
    }
    int num = 0;
    for (int i = 0; i < str.length(); i++)
    {
      num = num * 10 + (str[i] - '0');
    }

    return num;
  }
  void writeToFile(string filename = "sheet.txt")
  {
    char ch1 = 124;
    ofstream outputFile(filename);
    for (Cell *row = head; row != nullptr; row = row->down)
    {
      for (Cell *col = row; col != nullptr; col = col->right)
      {
        if (col->value.empty() || (std::find_if_not(col->value.begin(), col->value.end(), static_cast<int (*)(int)>(isspace)) == col->value.end()))
        {
          outputFile << "0" << ch1; // Write "0" instead of empty value
        }
        else

          outputFile << col->value << ch1;
      }
      outputFile << endl;
    }

    outputFile.close();
  }
  void loadfromfile(string filename = "sheet.txt")
  {
    Cell *temp = nullptr;
    char ch1 = 124;
    ifstream inputfile(filename);
    string line;
    for (int row = 0; getline(inputfile, line); row++)
    {
      stringstream ss(line);
      for (int col = 0; ss; col++)
      {
        string cellValue;
        getline(ss, cellValue, ch1); // Assuming values are separated by '|'

        Cell *newcell = new Cell(cellValue);
        if (cellValue.empty())
        {
          col--; // Adjust column count for empty cell
          break; // Exit the loop to avoid extra cell creation
        }

        if (row == 0)
        {
          if (head == nullptr)
          {
            head = newcell;
            current = newcell;
          }
          else
          {
            current->right = newcell;
            newcell->left = current;
            current = newcell;
          }
        }
        else
        {
          temp->down = newcell;
          newcell->up = temp;
          if (col != 0)
          {
            current->right = newcell;
            newcell->left = current;
          }
          current = newcell;
          temp = temp->right;
        }
      }

      // Move to the beginning of the next row
      while (current->left != nullptr)
      {
        current = current->left;
      }
      temp = current;
    }

    current = head;

    inputfile.close();
  }

  bool valid(string str)
  {
    for (char ch : str)
    {
      if (isdigit(ch))
      {
        return false; // Return false if any character is not a digit
      }
    }
    return !str.empty(); // Return false if the string is empty
  }
};
class Iterator
{
public:
  Cell *current_cell_;
  Iterator(Cell *head)
  {
    current_cell_ = head;
  }

  Iterator &operator++()
  {
    current_cell_ = current_cell_->up;
    return *this;
  }

  Iterator &operator--()
  {
    current_cell_ = current_cell_->down;
    return *this;
  }

  Iterator &operator--(int)
  {
    current_cell_ = current_cell_->left;
    return *this;
  }

  Iterator &operator++(int)
  {
    current_cell_ = current_cell_->right;
    return *this;
  }

  Cell *GetCurrentCell() { return current_cell_; }
};
void Runner(MiniExcel c1)
{
  while (true)
  {
    c1.print5by5();
    if (GetAsyncKeyState('W'))
    {
      c1.MoveCurrentUp();
    }
    if (GetAsyncKeyState('S'))
    {
      c1.MoveCurrentDown();
    }
    if (GetAsyncKeyState('A'))
    {
      c1.MoveCurrentLeft();
    }
    if (GetAsyncKeyState('D'))
    {
      c1.MoveCurrentRight();
    }
    if (GetAsyncKeyState('V'))
    {
      cin.clear();
      cin.sync();
      color1(6);
      string val;
      cout << "Enter value:";
      cin >> val;
      color1(7);
      c1.SetCurrentValue(val);
      system("cls");
    }
    if (GetAsyncKeyState('U'))
    {
      c1.InsertRowAboveCurrentCell();
      system("cls");
    }
    if (GetAsyncKeyState('B'))
    {
      c1.InsertRowBelowCurrentCell();
      system("cls");
    }
    if (GetAsyncKeyState('L'))
    {
      c1.InsertColLeftToCurrentCell();
      system("cls");
    }
    if (GetAsyncKeyState('N'))
    {
      c1.insertColumnRightToCurrentCell();
      system("cls");
    }
    if (GetAsyncKeyState('R'))
    {
      c1.InsertCellByRightShift();
      system("cls");
    }
    if (GetAsyncKeyState('E'))
    {
      c1.InsertCellByDownShift();
      system("cls");
    }
    if (GetAsyncKeyState('H'))
    {
      c1.DeleteCellByLeftShift();
      system("cls");
    }

    if (GetAsyncKeyState('J'))
    {
      c1.deleteRow();
      system("cls");
    }
    if (GetAsyncKeyState('K'))
    {
      c1.deleteCol();
      system("cls");
    }
    if (GetAsyncKeyState('C'))
    {
      c1.ClearRow();
      system("cls");
    }
    if (GetAsyncKeyState('X'))
    {
      c1.ClearCol();
      system("cls");
    }
    if (GetAsyncKeyState(VK_ESCAPE))
    {
      system("cls");
      break;
    }
    if (GetAsyncKeyState('Q'))
    {
      color1(6);
      int startingrange;
      int endingrange;
      int ans = -32764;
      cout << "Enter Start Cell:";
      cin >> startingrange;
      cout << "Enter Ending Cell:";
      cin >> endingrange;
      int opt;
      cout << "Which operation you want to perform(sum(1),avg(2),count(3),max(4),min(5)):";
      cin >> opt;
      if (opt == 1)
      {
        ans = c1.RangeSum(startingrange, endingrange);
      }
      else if (opt == 2)
      {
        ans = c1.RangeAvg(startingrange, endingrange);
      }
      else if (opt == 3)
      {
        ans = c1.Count(startingrange, endingrange);
      }
      else if (opt == 4)
      {
        ans = c1.Max(startingrange, endingrange);
      }
      else if (opt == 5)
      {
        ans = c1.Min(startingrange, endingrange);
      }
      else
      {
        cout << "wrong operation:";
        getch();
      }
      if (ans != -32764)
      {
        string val = to_string(ans);
        c1.SetCurrentValue(val);
      }
      system("cls");
      color1(7);
    }
    if (GetAsyncKeyState('Y'))
    {
      color1(9);
      int startingrange;
      int endingrange;
      cout << "Enter Start Cell:";
      cin >> startingrange;
      cout << "Enter Ending Cell:";
      cin >> endingrange;
      c1.Copy(startingrange, endingrange);
      c1.printcopycutdata();
      color1(7);
    }
    if (GetAsyncKeyState('T'))
    {
      color1(9);
      int startingrange;
      int endingrange;
      cout << "Enter Start Cell:";
      cin >> startingrange;
      cout << "Enter Ending Cell:";
      cin >> endingrange;
      c1.Cut(startingrange, endingrange);
      c1.printcopycutdata();
      Sleep(1999);
      system("cls");
      color1(7);
    }
    if (GetAsyncKeyState('P'))
    {
      c1.paste();
      system("cls");
    }
    if (GetAsyncKeyState(VK_TAB))
    {
      c1.writeToFile();
    }
  }
};

main()
{
  int value = 0;
  system("cls");
  while (true)
  {
    menu(value);
    Hide_Cursor();
    if (GetAsyncKeyState(VK_UP) & 0x8001)
    {
      if (value == 0)
      {
        value = 3;
      }
      else
      {
        value--;
      }
      Sleep(300);
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8001)
    {
      if (value == 3)
      {
        value = 0;
      }
      else
      {
        value++;
      }
      Sleep(300);
    }

    if (GetAsyncKeyState(VK_RETURN) & 0x8001)
    {
      if (GetAsyncKeyState(VK_RETURN) & 0x8001)
      {
        if (value == 0 && GetAsyncKeyState(VK_RETURN))
        {
          system("cls");
          MiniExcel c1(0);
          Runner(c1);
        }
        if (value == 1 && GetAsyncKeyState(VK_RETURN) & 0x8001)
        {
          system("cls");
          MiniExcel c1(1);
          Runner(c1);
        }
        if (value == 2 && GetAsyncKeyState(VK_RETURN) & 0x8001)
        {
          help();
          Sleep(1500);
          system("cls");
        }
        if (value == 3 && GetAsyncKeyState(VK_RETURN) & 0x8001)
        {
          break;
                }
      }
    }
  }
}
