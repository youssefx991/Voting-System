#ifndef CONSOLEUI_H_INCLUDED
#define CONSOLEUI_H_INCLUDED


#include <windows.h>

void gotoxy(int x, int y);

void drawVotingMenu(int current);

void blinkSelection(int y, int numOfBlinks);


void drawGuestMenu(int current);

#endif // CONSOLEUI_H_INCLUDED
