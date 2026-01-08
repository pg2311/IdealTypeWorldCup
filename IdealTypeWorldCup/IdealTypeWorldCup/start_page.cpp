#include "start_page.h"
#include "input.h"
#include "colors.h"
#include <iostream>

using namespace std;

void displayStart(int selected) {
    clearScreen();

    // Decorated title with colors
    wcout << L"╔════════════════════════════════════╗\n";
    wcout << L"║                                    ║\n";
    wcout << L"║           이상형 월드컵            ║\n";
    wcout << L"║                                    ║\n";
    wcout << L"╚════════════════════════════════════╝\n";
    wcout << L"\n";

    // Menu options with highlighting
    if (selected == 0) {
        wcout << L"           " << Color::SELECTED << L"  시작  " << Color::RESET << L"               \n";
        wcout << L"           " << Color::UNSELECTED << L"  종료  " << Color::RESET << L"               \n";
    }
    else {
        wcout << L"           " << Color::UNSELECTED << L"  시작  " << Color::RESET << L"               \n";
        wcout << L"           " << Color::SELECTED << L"  종료  " << Color::RESET << L"               \n";
    }

    wcout << L"\n";
    wcout << L"  [위/아래] 이동  [엔터] 선택\n";
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