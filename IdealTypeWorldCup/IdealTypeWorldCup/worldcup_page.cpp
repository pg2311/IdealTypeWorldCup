#include "worldcup_page.h"
#include "input.h"
#include <iostream>
#include <string>

using namespace std;

void displayMatch(string left, string right, int selected) {
    clearScreen();

    cout << "==================================\n";
    cout << "          WORLD CUP               \n";
    cout << "==================================\n\n";

    if (selected == 0) {
        cout << "   [" << left << "]     " << right << "   \n";
    }
    else {
        cout << "    " << left << "     [" << right << "]\n";
    }

    cout << "\n  [LEFT/RIGHT] Choose  [ENTER] Select\n";
}

void showWorldCupPage(int gender) {
    // Simple demo with 2 candidates
    string candidates[2];

    if (gender == 0) {
        candidates[0] = "Person A";
        candidates[1] = "Person B";
    }
    else {
        candidates[0] = "Person C";
        candidates[1] = "Person D";
    }

    int selected = 0;

    while (true) {
        displayMatch(candidates[0], candidates[1], selected);

        int key = getKey();

        if (key == KEY_LEFT) {
            selected = 0;
        }
        else if (key == KEY_RIGHT) {
            selected = 1;
        }
        else if (key == KEY_ENTER) {
            clearScreen();
            cout << "Winner: " << candidates[selected] << "!\n";
            break;
        }
    }
}