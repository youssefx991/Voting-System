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
            cout << "\033[47;30m> " <<menu[i] << " <\033[0m"<<RESET;
        else
            cout << "  " << menu[i];
    }
}



void blinkSelection(int y, int numOfBlinks)
{
    for (int i = 0; i < numOfBlinks; i++)
    {
        gotoxy(57, y);
        cout << "\033[42;30m    SELECTED     \033[0m";
        Sleep(150);

        gotoxy(57, y);
        cout << "                     ";
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
            cout << "  " << menu[i];
    }
}


