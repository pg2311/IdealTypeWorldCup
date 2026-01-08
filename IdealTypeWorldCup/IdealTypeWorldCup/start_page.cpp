#include "start_page.h"
#include "input.h"
#include <iostream>

using namespace std;

void displayStart(int selected) {
    clearScreen();

    wcout << L"==================================\n";
    wcout << L"                                  \n";
    wcout << L"     IDEAL TYPE WORLD CUP         \n";
    wcout << L"                                  \n";
    wcout << L"==================================\n\n";

    if (selected == 0) {
        wcout << L"        >  START  <               \n";
        wcout << L"           EXIT                   \n";
    }
    else {
        wcout << L"           START                  \n";
        wcout << L"        >  EXIT   <               \n";
    }

    wcout << L"\n  [UP/DOWN] Move  [ENTER] Select\n";
}

MenuChoice showStartPage() {
    int selected = 0;

    while (true) {
        displayStart(selected);

        int key = getKey();

        if (key == KEY_UP) {
            selected--;
            if (selected < 0) selected = 1;
        }
        else if (key == KEY_DOWN) {
            selected++;
            if (selected > 1) selected = 0;
        }
        else if (key == KEY_ENTER) {
            return static_cast<MenuChoice>(selected);
        }
    }
}