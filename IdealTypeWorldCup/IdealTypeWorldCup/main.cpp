#include "start_page.h"
#include "settings_page.h"
#include "worldcup_page.h"
#include "input.h"
#include "colors.h"
#include <iostream>
#include <windows.h>
#include <locale>
#include <io.h>
#include <fcntl.h>

using namespace std;

int main() {
    // Enable ANSI escape sequences on Windows console
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    // Set console to Unicode mode for proper Korean display
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    // Step 1: Start Page
    MenuChoice startChoice = showStartPage();

    if (startChoice == MenuChoice::EXIT) {
        clearScreen();
        wcout << L"안녕히 가세요!" << L"\n";
        return 0;
    }

    // Step 2: Settings Page
    Gender gender = showSettingsPage();

    // Step 3: World Cup Page
    showWorldCupPage(gender);

    return 0;
}