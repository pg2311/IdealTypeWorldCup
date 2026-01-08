#include "worldcup_page.h"
#include "input.h"
#include "photo.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void displayMatch(int left_photo, int right_photo, wstring left_name, wstring right_name, int selected, int round, int match_num, int total_matches) {
    clearScreen();

    wcout << L"====================================================================\n";
    wcout << L"          WORLD CUP               ";

    // Display round information
    if (round == 8)
        wcout << L"       ROUND OF 8 - Match " << match_num << L"/" << total_matches << L"\n";
    else if (round == 4)
        wcout << L"      SEMI FINALS - Match " << match_num << L"/" << total_matches << L"\n";
    else if (round == 2)
        wcout << L"          FINALS\n";

    wcout << L"====================================================================\n";

    // Display photos side by side (trim left/right, limit height, skip top)
    printPhotoSideBySide(left_photo, right_photo, selected, 8, 8, 37, 8);

    wcout << L"\n";
    if (selected == 0) {
        wcout << L"        [" << left_name << L"]";
        wcout << L"              " << right_name << L"\n";
    }
    else {
        wcout << L"         " << left_name;
        wcout << L"              [" << right_name << L"]\n";
    }
}

void showWorldCupPage(int gender) {
    // Initialize candidates based on gender
    // Male: photos 1-8, Female: photos 9-16
    vector<int> current_round;
    int photo_start = (gender == 0) ? 1 : 9;

    for (int i = 0; i < 8; i++) {
        current_round.push_back(photo_start + i);
    }

    // Tournament loop - continue until one winner
    while (current_round.size() > 1) {
        vector<int> next_round;
        int round_size = (int)current_round.size();
        int total_matches = round_size / 2;

        // Process all matches in current round
        for (int match_idx = 0; match_idx < round_size; match_idx += 2) {
            int left_photo = current_round[match_idx];
            int right_photo = current_round[match_idx + 1];
            int selected = 0;

            // Match loop
            while (true) {
                displayMatch(
                    left_photo, right_photo,
                    names[left_photo - 1], names[right_photo - 1],
                    selected, round_size, (match_idx / 2) + 1, total_matches
                );

                int key = getKey();

                if (key == KEY_LEFT) {
                    selected = 0;
                }
                else if (key == KEY_RIGHT) {
                    selected = 1;
                }
                else if (key == KEY_ENTER) {
                    // Winner advances to next round
                    if (selected == 0)
                        next_round.push_back(left_photo);
                    else
                        next_round.push_back(right_photo);
                    break;
                }
            }
        }

        // Move to next round
        current_round = next_round;
    }

    // Display final winner
    clearScreen();
    wcout << L"==================================\n";
    wcout << L"          CHAMPION!               \n";
    wcout << L"==================================\n\n";

    printphoto(current_round[0], 37, 8);

    wcout << L"\n\n";
    wcout << L"      Winner: " << names[current_round[0] - 1] << L"!\n\n";
    wcout << L"  Press any key to exit...\n";
    getKey();
}