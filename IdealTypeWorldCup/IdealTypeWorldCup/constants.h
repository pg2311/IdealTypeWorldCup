#ifndef CONSTANTS_H
#define CONSTANTS_H

// Enum classes for type safety
enum class Gender {
    MALE = 0,
    FEMALE = 1
};

enum class MenuChoice {
    START = 0,
    EXIT = 1
};

// Photo-related constants
constexpr int PHOTO_START_MALE = 1;
constexpr int PHOTO_START_FEMALE = 9;
constexpr int PHOTOS_PER_GENDER = 8;

// Display constants for photo rendering
constexpr int TRIM_LEFT = 6;
constexpr int TRIM_RIGHT = 7;
constexpr int MAX_HEIGHT = 37;
constexpr int SKIP_TOP = 9;

// Array size constants
constexpr int MAX_NAMES = 20;
constexpr int MAX_NAME_LENGTH = 100;

// Menu option counts
constexpr int START_MENU_OPTIONS = 2;  // START, EXIT
constexpr int GENDER_OPTIONS = 2;      // MALE, FEMALE

// Tournament constants
constexpr int TOURNAMENT_START_SIZE = 8;  // Round of 8

#endif // CONSTANTS_H
