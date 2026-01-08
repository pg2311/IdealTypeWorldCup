#ifndef COLORS_H
#define COLORS_H

#include <string>

// ANSI Escape Code namespace for console colors and formatting
namespace Color {
    // Reset
    const std::wstring RESET = L"\033[0m";

    // Text formatting
    const std::wstring BOLD = L"\033[1m";
    const std::wstring DIM = L"\033[2m";
    const std::wstring UNDERLINE = L"\033[4m";

    // Pastel foreground colors (bright variants for softer look)
    const std::wstring PASTEL_PINK = L"\033[95m";      // Light magenta
    const std::wstring PASTEL_BLUE = L"\033[94m";      // Light blue
    const std::wstring PASTEL_CYAN = L"\033[96m";      // Light cyan
    const std::wstring PASTEL_GREEN = L"\033[92m";     // Light green
    const std::wstring PASTEL_YELLOW = L"\033[93m";    // Light yellow
    const std::wstring PASTEL_PURPLE = L"\033[35m";    // Magenta
    const std::wstring WHITE = L"\033[97m";            // Bright white
    const std::wstring GRAY = L"\033[90m";             // Dark gray
    const std::wstring BLACK = L"\033[30m";

    // Background colors for highlighting
    const std::wstring BG_PASTEL_BLUE = L"\033[104m";  // Light blue background
    const std::wstring BG_PASTEL_CYAN = L"\033[106m";  // Light cyan background
    const std::wstring BG_PASTEL_PINK = L"\033[105m";  // Light magenta background
    const std::wstring BG_DARK = L"\033[100m";         // Dark gray background
    const std::wstring BG_WHITE = L"\033[47m";

    // Combined styles for common uses
    const std::wstring TITLE = BOLD + PASTEL_CYAN;
    const std::wstring SELECTED = BOLD + PASTEL_YELLOW + BG_DARK;
    const std::wstring UNSELECTED = GRAY;
    const std::wstring HIGHLIGHT = PASTEL_PINK;
    const std::wstring INFO = PASTEL_BLUE;
    const std::wstring SUCCESS = PASTEL_GREEN;
    const std::wstring BORDER = PASTEL_PURPLE;
    const std::wstring NAME = PASTEL_CYAN;
    const std::wstring ROUND_INFO = PASTEL_YELLOW;

    // ANSI control codes
    const std::wstring CLEAR_SCREEN = L"\033[2J\033[H";  // Clear screen and move cursor to home
}

#endif // COLORS_H
