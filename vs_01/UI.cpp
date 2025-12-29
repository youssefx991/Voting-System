#include "UI.h"
#include <iostream>


using namespace std;

// colors definitions
const char* RESET  = "\033[0m";
const char* RED    = "\033[31m";
const char* GREEN  = "\033[32m";
const char* YELLOW = "\033[33m";
const char* BLUE   = "\033[34m";
const char* CYAN   = "\033[36m";
const char* BOLD   = "\033[1m";

// ===== ANIMATION FUNCTION =====
void loading(const string& text, int dotCount, int delayMs) {
    cout << CYAN << text;
    for (int i = 0; i < dotCount; i++) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
    cout << RESET << endl;
}
