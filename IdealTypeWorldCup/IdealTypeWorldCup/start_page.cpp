#include "start_page.h"
#include "input.h"
#include <iostream>

using namespace std;

void displayStart(int selected) {
    clearScreen();

    cout << "==================================\n";
    cout << "                                  \n";
    cout << "     IDEAL TYPE WORLD CUP         \n";
    cout << "                                  \n";
    cout << "==================================\n\n";

    if (selected == 0) {
        cout << "        >  START  <               \n";
        cout << "           EXIT                   \n";
    }
    else {
        cout << "           START                  \n";
        cout << "        >  EXIT   <               \n";
    }

    cout << "\n  [UP/DOWN] Move  [ENTER] Select\n";
}

int showStartPage() {
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
            return selected;
        }
    }
}