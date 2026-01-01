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
    else
        if(numOFmenu==2)x=48;

    string message ="\033[42;30m    SELECTED     \033[0m";
    string space ="                  ";

    if(numOFmenu==1)
    {
        message ="\033[42;30m       SELECTED         \033[0m";
        space ="                         ";
    }
    if(numOFmenu==2)
    {
        message ="\033[42;30m         SELECTED         \033[0m";
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

    gotoxy(50, 7);
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


void drawCandidateAuthMenu(int current)
{
    int y = 7;

    gotoxy(45, y); y += 2;
    cout << "===== CANDIDATE AUTH MENU =====";

    const char* options[] =
    {
        "Login",
        "Register",
        "Back "
    };

    for (int i = 0; i < 3; i++)
    {
        gotoxy(55, y); y += 2;

        if (current == i)
            cout << "\033[47;30m> " << options[i] << " <\033[0m";
        else
            cout << "  " << options[i]<< "  ";
    }

    gotoxy(45, y + 1);
    cout << "==============================";
}

static void drawBox(int x, int y, int width)
{
    gotoxy(x, y);
    cout << "\033[47;30m";
    for (int i = 0; i < width; i++) cout << " ";
    cout << "\033[0m";
}

string inputField(int x, int y, int maxLen, bool isPassword)
{
    string text;
    int current = 0;

    drawBox(x, y, maxLen + 1);

    while (true)
    {
        gotoxy(x + current, y);
        char key = _getch();

        // extended key
        if (key == -32)
        {
            key = _getch();
            switch (key)
            {
            case 75: if (current > 0) current--; break;      // left
            case 77: if (current < (int)text.size()) current++; break; // right
            case 71: current = 0; break;                     // home
            case 79: current = text.size(); break;           // end
            case 83:                                         // delete
                if (current < (int)text.size())
                    text.erase(current, 1);
                break;
            }
        }
        else
        {
            switch (key)
            {
            case 8: // backspace
                if (current > 0)
                {
                    current--;
                    text.erase(current, 1);
                }
                break;

            case 13: // enter
                return text;

            case 27: // esc
                return "";

            default:
                if ((int)text.size() < maxLen && key >= 32)
                {
                    text.insert(text.begin() + current, key);
                    current++;
                }
            }
        }

      drawBox(x, y, maxLen + 1);
      gotoxy(x, y);

        cout << "\033[47;30m";   // white bg, black text

        for (int i = 0; i < (int)text.size(); i++)
        {
            if (isPassword)
                cout << "*";
            else
                cout << text[i];
        }

        cout << "\033[0m";
    }
}

