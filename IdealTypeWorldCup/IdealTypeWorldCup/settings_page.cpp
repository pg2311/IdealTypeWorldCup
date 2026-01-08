#include "settings_page.h"
#include "input.h"
#include <iostream>

using namespace std;

void displaySettings(int selected) {
    clearScreen();

    cout << "==================================\n";
    cout << "            SETTINGS              \n";
    cout << "==================================\n\n";

    cout << "      Select Version:\n\n";

    if (selected == 0) {
        cout << "      [ MALE ]    FEMALE  \n";
    }
    else {
        cout << "        MALE    [ FEMALE ]\n";
    }

    cout << "\n  [LEFT/RIGHT] Change  [ENTER] Confirm\n";
}

int showSettingsPage() {
    int selected = 0;  // 0 = Male, 1 = Female

    while (true) {
        displaySettings(selected);

        int key = getKey();

        if (key == KEY_LEFT) {
            selected = 0;
        }
        else if (key == KEY_RIGHT) {
            selected = 1;
        }
        else if (key == KEY_ENTER) {
            return selected;
        }
    }
}