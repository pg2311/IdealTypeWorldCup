#include "worldcup_page.h"
#include "input.h"
#include "photo.h"
#include "constants.h"
#include "colors.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

void displayMatch(int left_photo, int right_photo, wstring left_name, wstring right_name, int selected, int round, int match_num, int total_matches) {
    clearScreen();

    // Decorated title with round information
    wcout << Color::BORDER << L"╔══════════════════════════════════════════════════════════════════╗\n";
    wcout << L"║  " << Color::TITLE << L"          월드컵               ";

    // Display round information with colors
    if (round == 8)
        wcout << Color::ROUND_INFO << L"     8강 - " << match_num << L"/" << total_matches << L" 경기    " << Color::BORDER;
    else if (round == 4)
        wcout << Color::ROUND_INFO << L"  준결승 - " << match_num << L"/" << total_matches << L" 경기    " << Color::BORDER;
    else if (round == 2)
        wcout << Color::ROUND_INFO << L"          결승         " << Color::BORDER;

    wcout << L"          ║\n";
    wcout << L"╚══════════════════════════════════════════════════════════════════╝" << Color::RESET << L"\n";

    // Display photos side by side (trim left/right, limit height, skip top)
    printPhotoSideBySide(left_photo, right_photo, selected, TRIM_LEFT, TRIM_RIGHT, MAX_HEIGHT, SKIP_TOP);

    wcout << L"\n";
    // Display names with highlighting
    if (selected == 0) {
        wcout << L"        " << Color::SELECTED << L" " << left_name << L" " << Color::RESET;
        wcout << L"              " << Color::UNSELECTED << right_name << Color::RESET << L"\n";
    }
    else {
        wcout << L"        " << Color::UNSELECTED << left_name << Color::RESET;
        wcout << L"              " << Color::SELECTED << L" " << right_name << L" " << Color::RESET << L"\n";
    }
}

void showWorldCupPage(Gender gender) {
    // Initialize candidates based on gender
    // Male: photos 1-8, Female: photos 9-16
    vector<int> current_round;
    int photo_start = (gender == Gender::MALE) ? PHOTO_START_MALE : PHOTO_START_FEMALE;

    for (int i = 0; i < PHOTOS_PER_GENDER; i++) {
        current_round.push_back(photo_start + i);
    }

    // Shuffle candidates for random matchups
    random_device rd;
    mt19937 gen(rd());
    shuffle(current_round.begin(), current_round.end(), gen);

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

    // Decorated winner title
    wcout << Color::BORDER << L"╔════════════════════════════════════╗\n";
    wcout << L"║                                    ║\n";
    wcout << L"║  " << Color::SUCCESS << L"           우승!              " << Color::BORDER << L"    ║\n";
    wcout << L"║                                    ║\n";
    wcout << L"╚════════════════════════════════════╝" << Color::RESET << L"\n";

    printPhoto(current_round[0], MAX_HEIGHT, SKIP_TOP);

    wcout << Color::HIGHLIGHT << L"      우승자: " << Color::NAME << names[current_round[0] - 1] << Color::HIGHLIGHT << L"!" << Color::RESET << L"\n";
    wcout << Color::INFO << L"  아무 키나 눌러 종료..." << Color::RESET;
    getKey();
}