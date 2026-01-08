#ifndef PHOTO_H
#define PHOTO_H

#include <string>

// Function declarations
void printphoto(int photo_no, int max_height = 0, int skip_top = 0);
void printPhotoSideBySide(int left_photo, int right_photo, int selected, int trim_left = 0, int trim_right = 0, int max_height = 0, int skip_top = 0);

// External declaration for names array
extern wchar_t names[20][100];

#endif // PHOTO_H