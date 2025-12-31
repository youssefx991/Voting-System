#include "ConsoleUI.h"
#include "UI.h"

#include <iostream>
#include <limits>
#include<windows.h>
#include <conio.h>
#include <string.h>


using namespace std;
void gotoxy(int x, int y)
{
    COORD c = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void drawVotingMenu(int current)
{
    const char* menu[] = {
        "   Guest   ",
        " Candidate ",
        "   Admin   ",
        "   Voter   ",
        "   Exit    "
    };

    gotoxy(45, 7);
    cout << "===== VOTING SYSTEM MAIN MENU =====";

    for (int i = 0; i < 5; i++)
    {
        gotoxy(57, 9 + i * 2);

        if (i == current)
            cout << "\033[47;30m> " <<menu[i] << " <\033[0m";
        else
            cout << "  " << menu[i]<<"  ";
    }
}



void blinkSelection(int y, int numOfBlinks, int numOFmenu)
{
    int x;
    if(numOFmenu==0)x=57;

    else
        if (numOFmenu==1)x=50;

    string message ="\033[42;30m    SELECTED     \033[0m";
    string space ="                  ";

    if(numOFmenu==1)
    {
        message ="\033[42;30m       SELECTED         \033[0m";
        space ="                         ";
    }
    for (int i = 0; i < numOfBlinks; i++)
    {
        gotoxy(x, y);
        cout <<message ;
        Sleep(150);

        gotoxy(x, y);
        cout << space;
        Sleep(150);
    }
}

void drawGuestMenu(int current)
{
    const char* menu[] = {
        "View Voting Rules",
        "View All Elections",
        "View All Candidates",
        "Back to Main Menu"
    };

    gotoxy(45, 7);
    cout << "===== GUEST MENU =====";

    for (int i = 0; i < 4; i++)
    {
        gotoxy(50, 9 + i * 2);

        if (i == current)
            cout << "\033[47;30m> " << menu[i] << " <\033[0m";
        else
            cout << "  " << menu[i]<<"  ";
    }
}


