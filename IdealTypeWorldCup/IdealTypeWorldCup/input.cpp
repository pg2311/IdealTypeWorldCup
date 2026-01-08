#include "input.h"
#include <iostream>
#include <conio.h>  // Windows-only header for keyboard input

using namespace std;

int getKey() {
    int ch = _getch();  // Read one key without Enter

    // Arrow keys on Windows send TWO codes
    // First: 224 (or 0), Second: the actual key
    if (ch == 224 || ch == 0) {
        ch = _getch();  // Get the second code
        switch (ch) {
        case 72: return KEY_UP;     // Up arrow
        case 80: return KEY_DOWN;   // Down arrow
        case 75: return KEY_LEFT;   // Left arrow
        case 77: return KEY_RIGHT;  // Right arrow
        default: return KEY_UNKNOWN;
        }
    }
    else if (ch == 13) {  // Enter key on Windows
        return KEY_ENTER;
    }

    return ch;
}

void clearScreen() {
    system("cls");  // Windows clear screen command
}