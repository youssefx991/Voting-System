#ifndef UI_H
#define UI_H

#include <string>
#include <thread>
#include <chrono>

// main colors
// extern declarations match definitions in UI.cpp 
extern const char* RESET;
extern const char* RED;
extern const char* GREEN;
extern const char* YELLOW;
extern const char* BLUE;
extern const char* CYAN;
extern const char* BOLD;

//  simple loading animation 
void loading(const std::string& text, int dotCount = 10, int delayMs = 300);

#endif
