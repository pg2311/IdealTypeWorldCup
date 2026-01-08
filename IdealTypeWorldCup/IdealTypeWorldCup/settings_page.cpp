#include "settings_page.h"
#include "input.h"
#include <iostream>

using namespace std;

void displaySettings(int selected) {
    clearScreen();

    wcout << L"==================================\n";
    wcout << L"            SETTINGS              \n";
    wcout << L"==================================\n\n";

    wcout << L"      Select Version:\n\n";

    if (selected == 0) {
        wcout << L"      [ MALE ]    FEMALE  \n";
    }
    else {
        wcout << L"        MALE    [ FEMALE ]\n";
    }

    wcout << L"\n  [LEFT/RIGHT] Change  [ENTER] Confirm\n";
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