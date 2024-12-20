#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <conio.h>
#include <ctime>
#include <iomanip>

using namespace std;

int i, j, li, lp, rec, valid;
COORD coord = {0, 0};

void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class DRAW
{
public:
    void LINE_HOR(int, int, int, char);
    void LINE_VER(int, int, int, char);
    void BOX(int, int, int, int, char);
};

class FEE
{
private:
    int Class;
    float tuition, ac, science, computer, activity;
    void DISPLAY(int);
    void MODIFY_RECORD(int, float, float, float, float, float);

public:
    void ADDITION(void);
    void MODIFICATION(void);
    void FEE_SLIP(void);
    void LIST(void);
    void HELP(void);
} fee;

void mainmenu()
{
    system("cls");

    for (li = 30; li <= 50; li++)
    {
        gotoxy(li, 14);
        Sleep(30);
        cout << "*";
    }
    for (li = 50; li >= 30; li--)
    {
        gotoxy(li, 30);
        Sleep(30);
        cout << "*";
    }
    for (lp = 15; lp < 30; lp++)
    {
        gotoxy(30, lp);
        Sleep(100);
        cout << "|";
    }
    for (lp = 29; lp >= 15; lp--)
    {
        gotoxy(50, lp);
        Sleep(100);
        cout << "|";
    }

    gotoxy(15, 10);
    cout << "Press the corresponding Keys for the desired action..";
    gotoxy(35, 16);
    cout << "F: FEE SLIP";
    gotoxy(35, 19);
    cout << "M: MODIFY";
    gotoxy(35, 22);
    cout << "L: LIST";
    gotoxy(35, 25);
    cout << "H: HELP";
    gotoxy(35, 28);
    cout << "Q: QUIT";

    char choice = getch();
    char ch = toupper(choice);
    switch (ch)
    {
    case 'F':
        fee.FEE_SLIP();
        break;
    case 'M':
        fee.MODIFICATION();
        break;
    case 'L':
        fee.LIST();
        break;
    case 'H':
        fee.HELP();
        break;
    case 'Q':
        exit(0);
        break;
    default:
        gotoxy(33, 40);
        cout << "Illegal Choice Press any key to return to Main Menu";
        getch();
        mainmenu();
    }
}

void DRAW::LINE_HOR(int column1, int column2, int row, char c)
{
    for (; column1 <= column2; column1++)
    {
        gotoxy(column1, row);
        cout << c;
    }
}

void DRAW::LINE_VER(int row1, int row2, int column, char c)
{
    for (; row1 <= row2; row1++)
    {
        gotoxy(column, row1);
        cout << c;
    }
}

void DRAW::BOX(int column1, int row1, int column2, int row2, char c)
{
    char ch = 218;
    char c1, c2, c3, c4;
    char l1 = 196, l2 = 179;

    if (c == ch)
    {
        c1 = 218;
        c2 = 191;
        c3 = 192;
        c4 = 217;
        l1 = 196;
        l2 = 179;
    }
    else
    {
        c1 = c;
        c2 = c;
        c3 = c;
        c4 = c;
        l1 = c;
        l2 = c;
    }

    gotoxy(column1, row1);
    cout << c1;
    gotoxy(column2, row1);
    cout << c2;
    gotoxy(column1, row2);
    cout << c3;
    gotoxy(column2, row2);
    cout << c4;

    column1++;
    column2--;
    LINE_HOR(column1, column2, row1, l1);
    LINE_HOR(column1, column2, row2, l1);

    column1--;
    column2++;
    row1++;
    row2--;
    LINE_VER(row1, row2, column1, l2);
    LINE_VER(row1, row2, column2, l2);
}

void FEE::ADDITION(void)
{
    fstream file;
    file.open("FEE.DAT", ios::in);
    if (!file.fail())
        return;

    file.close();
    file.open("FEE.DAT", ios::app);
    for (int i = 1; i <= 12; i++)
    {
        Class = i;
        tuition = 0.0;
        ac = 0.0;
        science = 0.0;
        computer = 0.0;
        activity = 0.0;
        file.write((char *)this, sizeof(FEE));
    }
    file.close();
    MODIFY_RECORD(12, 450, 50, 60, 60, 50);
    MODIFY_RECORD(11, 450, 50, 60, 60, 50);
    MODIFY_RECORD(10, 350, 50, 30, 60, 50);
    MODIFY_RECORD(9, 350, 50, 20, 60, 50);
    MODIFY_RECORD(8, 300, 50, 20, 40, 50);
    MODIFY_RECORD(7, 300, 50, 20, 40, 50);
    MODIFY_RECORD(6, 300, 50, 20, 40, 50);
    MODIFY_RECORD(5, 250, 50, 0, 40, 40);
    MODIFY_RECORD(4, 250, 50, 0, 40, 40);
    MODIFY_RECORD(3, 250, 50, 0, 40, 40);
    MODIFY_RECORD(2, 250, 50, 0, 40, 40);
    MODIFY_RECORD(1, 250, 50, 0, 40, 40);
}

void FEE::LIST()
{
    system("cls");
    DRAW d;
    d.BOX(1, 2, 80, 24, 218);
        gotoxy(3, 1);
    cout << "Class-wise Fee Structure";
    gotoxy(3, 3);
    cout << setw(8) << "CLASS" 
         << setw(15) << "TUITION" 
         << setw(15) << "AC" 
         << setw(15) << "SCIENCE" 
         << setw(15) << "COMPUTER" 
         << setw(15) << "ACTIVITY";
    
    fstream file;
    file.open("FEE.DAT", ios::in);
    int row = 5;

    while (file.read((char *)this, sizeof(FEE)))
    {
        gotoxy(3, row);
        cout << setw(8) << Class 
             << setw(15) << tuition 
             << setw(15) << ac 
             << setw(15) << science 
             << setw(15) << computer 
             << setw(15) << activity;
        row++;
    }
    file.close();
    gotoxy(3, 23);
    cout << "Press any key to return to the main menu...";
    getch();
    mainmenu();
}

void FEE::MODIFICATION()
{
    system("cls");
    int c;
    float t, a, s, comp, act;
    gotoxy(5, 5);
    cout << "Enter the class (1-12) to modify: ";
    cin >> c;
    gotoxy(5, 7);
    cout << "Enter Tuition Fee: ";
    cin >> t;
    gotoxy(5, 8);
    cout << "Enter AC Fee: ";
    cin >> a;
    gotoxy(5, 9);
    cout << "Enter Science Fee: ";
    cin >> s;
    gotoxy(5, 10);
    cout << "Enter Computer Fee: ";
    cin >> comp;
    gotoxy(5, 11);
    cout << "Enter Activity Fee: ";
    cin >> act;

    MODIFY_RECORD(c, t, a, s, comp, act);
    gotoxy(5, 13);
    cout << "Record updated successfully!";
    getch();
    mainmenu();
}

void FEE::MODIFY_RECORD(int c, float t, float a, float s, float comp, float act)
{
    fstream file;
    file.open("FEE.DAT", ios::in | ios::out | ios::binary);
    while (file.read((char *)this, sizeof(FEE)))
    {
        if (Class == c)
        {
            tuition = t;
            ac = a;
            science = s;
            computer = comp;
            activity = act;
            int pos = -1 * int(sizeof(FEE));
            file.seekp(pos, ios::cur);
            file.write((char *)this, sizeof(FEE));
            break;
        }
    }
    file.close();
}

void FEE::FEE_SLIP()
{
    system("cls");
    int c;
    gotoxy(5, 5);
    cout << "Enter the class to generate fee slip (1-12): ";
    cin >> c;

    fstream file;
    file.open("FEE.DAT", ios::in);
    while (file.read((char *)this, sizeof(FEE)))
    {
        if (Class == c)
        {
            system("cls");
            gotoxy(5, 5);
            cout << "Fee Slip for Class: " << Class;
            gotoxy(5, 7);
            cout << "Tuition Fee: " << tuition;
            gotoxy(5, 8);
            cout << "AC Fee: " << ac;
            gotoxy(5, 9);
            cout << "Science Fee: " << science;
            gotoxy(5, 10);
            cout << "Computer Fee: " << computer;
            gotoxy(5, 11);
            cout << "Activity Fee: " << activity;
            gotoxy(5, 13);
            cout << "Total Fee: " << tuition + ac + science + computer + activity;
            break;
        }
    }
    file.close();
    gotoxy(5, 15);
    cout << "Press any key to return to the main menu...";
    getch();
    mainmenu();
}

void FEE::HELP()
{
    system("cls");
    gotoxy(5, 5);
    cout << "Help Section";
    gotoxy(5, 7);
    cout << "1. Use 'F' for Fee Slip generation.";
    gotoxy(5, 8);
    cout << "2. Use 'M' to Modify Fee Records.";
    gotoxy(5, 9);
    cout << "3. Use 'L' to List all Fee Structures.";
    gotoxy(5, 10);
    cout << "4. Use 'H' for this Help section.";
    gotoxy(5, 11);
    cout << "5. Use 'Q' to Quit the program.";
    gotoxy(5, 13);
    cout << "Press any key to return to the main menu...";
    getch();
    mainmenu();
}

int main()
{
    fee.ADDITION();
    mainmenu();
    return 0;
}

