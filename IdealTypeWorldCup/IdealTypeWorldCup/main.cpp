#include "start_page.h"
#include "settings_page.h"
#include "worldcup_page.h"
#include "input.h"
#include <iostream>

using namespace std;

int main() {
    // Step 1: Start Page
    int startChoice = showStartPage();

    if (startChoice == 1) {  // Exit selected
        clearScreen();
        cout << "Goodbye!\n";
        return 0;
    }

    // Step 2: Settings Page
    int gender = showSettingsPage();

    // Step 3: World Cup Page
    showWorldCupPage(gender);

    return 0;
}