#include "settings_page.h"
#include "input.h"
#include "colors.h"
#include <iostream>

using namespace std;

void displaySettings(int selected) {
    clearScreen();

    // Decorated title with colors
    wcout << L"╔════════════════════════════════════╗\n";
    wcout << L"║              설정                  ║\n";
    wcout << L"╚════════════════════════════════════╝\n";

    wcout << L"버전 선택:\n";

    // Gender options with highlighting
    if (selected == 0) {
        wcout << L"        " << Color::SELECTED << L"  남자  " << Color::RESET;
        wcout << L"      " << Color::UNSELECTED << L"  여자  " << Color::RESET << L"\n";
    }
    else {
        wcout << L"        " << Color::UNSELECTED << L"  남자  " << Color::RESET;
        wcout << L"      " << Color::SELECTED << L"  여자  " << Color::RESET << L"\n";
    }

    wcout << L"\n\n";
    wcout << L"  [왼쪽/오른쪽] 변경  [엔터] 확인\n";
}

Gender showSettingsPage() {
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
            return static_cast<Gender>(selected);
        }
    }
}