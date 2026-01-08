#ifndef INPUT_H
#define INPUT_H

// Key codes for easy use
enum Key {
    KEY_UP = 1000,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_ENTER,
    KEY_UNKNOWN
};

// Read a single key (handles arrow keys)
int getKey();

// Clear the screen
void clearScreen();

#endif