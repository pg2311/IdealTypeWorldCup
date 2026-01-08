# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is an "Ideal Type World Cup" console application built in C++ using Visual Studio. It's a Windows console-based interactive game where users select their ideal type through a tournament-style interface. The application displays ASCII art photos stored in text files and uses keyboard navigation.

## Build and Run

This is a Visual Studio C++ project (`.vcxproj`).

**Building:**
- Open `IdealTypeWorldCup.sln` in Visual Studio
- Build using Visual Studio (Ctrl+Shift+B) or MSBuild from command line
- Configurations: Debug/Release for Win32/x64 platforms
- Uses Platform Toolset v143 (Visual Studio 2022)

**Running:**
- The executable is built to `x64/Debug/IdealTypeWorldCup.exe` (Debug) or `x64/Release/` (Release)
- Run from Visual Studio (F5) or execute the binary directly

**Platform:**
- Windows-only (uses `<conio.h>` for keyboard input and `system("cls")` for screen clearing)

## Architecture

**Navigation Flow:**
The application follows a linear three-page flow controlled from `main.cpp:9-26`:

1. **Start Page** → User chooses START or EXIT
2. **Settings Page** → User selects gender version (Male/Female)
3. **World Cup Page** → Tournament interface for selecting ideal type

**Key Components:**

- **Input Module** (`input.cpp/h`): Centralized keyboard input handling
  - `getKey()`: Reads keyboard input, handles arrow keys (Windows-specific scan codes)
  - `clearScreen()`: Clears console using `system("cls")`
  - Defines `Key` enum for UP/DOWN/LEFT/RIGHT/ENTER

- **Photo Module** (`photo.cpp/h`): Displays ASCII art from text files
  - `printphoto(int photo_no)`: Reads and displays `imgs/{photo_no}.txt`
  - `names[20][100]`: Global array of candidate names (currently in Korean encoding)
  - Photos are ASCII art stored as plain text files (see `imgs/1.txt` for example)

- **Page Modules**: Each page follows the same pattern
  - `display*()` function: Renders UI with current selection highlighted
  - `show*Page()` function: Main loop handling input and state
  - Uses bracket notation `[...]` to indicate selected items

**State Management:**
- Gender selection: `0` = Male, `1` = Female
- Menu selections tracked with integer indices
- No persistent state between runs

**Data Structure:**
- `imgs/` directory contains numbered `.txt` files (1.txt through 16.txt) with ASCII art
- Photos are loaded dynamically based on selection

## Code Conventions

- All page display functions use `clearScreen()` before rendering
- Selection UI uses `[ item ]` brackets to show current choice
- Navigation instructions displayed at bottom of each screen
- Return values: Most functions return integer codes (0/1) for binary choices

## Important Notes

- The codebase uses Windows-specific APIs (`_getch()`, `system("cls")`)
- Character encoding may need attention for the Korean names in `photo.cpp:9-26`
- TODO items exist in `worldcup_page.cpp:28-29` for randomization and removing magic numbers
- ASCII art photos must be in `imgs/` directory for the app to function
