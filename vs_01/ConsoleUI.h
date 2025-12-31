#ifndef CONSOLEUI_H_INCLUDED
#define CONSOLEUI_H_INCLUDED


#include <windows.h>
#include <string.h>
#include <iostream>


void gotoxy(int x, int y);

void drawVotingMenu(int current);

void blinkSelection(int y, int numOfBlinks, int numOFmenu=0);


void drawGuestMenu(int current);

void drawCandidateAuthMenu(int current);

std::string inputField(int x, int y, int maxLen, bool isPassword = false);
#endif // CONSOLEUI_H_INCLUDED
