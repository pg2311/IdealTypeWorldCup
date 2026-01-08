# Implementation Plan v2: Side-by-Side Photo Display

## Overview
Display two ASCII art photos side-by-side, highlight the selected one, and implement tournament progression.

## Changes Required

### 1. Photo Module (`photo.cpp/h`)

Add function: `void printPhotoSideBySide(int left_photo, int right_photo, int selected)`

**Logic:**
1. Read both photo files into `vector<string>` arrays
2. Loop through lines and print: `left_line + spacing + right_line`
3. Add highlight marker (`>>>` prefix or similar) to selected side

**Example output:**
```
>>> +---------+          +---------+
>>>  |  Photo  |           |  Photo  |
>>>  |   1     |           |   2     |
>>> +---------+          +---------+
```

### 2. World Cup Page (`worldcup_page.cpp`)

**Tournament structure:**
```cpp
vector<int> candidates;  // Current round photo indices
int match_idx = 0;       // Current match position
```

**Flow:**
1. Initialize `candidates` with 8 photo indices (based on gender)
2. Match loop:
   - Get two candidates: `candidates[match_idx]` and `candidates[match_idx+1]`
   - Display with `printPhotoSideBySide(photo1, photo2, selected)`
   - User selects with LEFT/RIGHT, confirms with ENTER
   - Store winner in `next_round` vector
   - Increment `match_idx += 2`
3. When round completes: `candidates = next_round`, reset `match_idx`
4. Repeat until one winner remains

**Display:**
```
==================================
       ROUND OF 8 - Match 1/4
==================================
[Photo 1]     [Photo 2]
  Person A      Person B

[LEFT/RIGHT] Choose  [ENTER] Select
```

### 3. Gender-Based Photo Selection

- Male (gender=0): Use photos 0-7
- Female (gender=1): Use photos 8-15
- Pass photo index (not `8 + selected`) to print function

## Implementation Order

1. Create `printPhotoSideBySide()` - handle file reading and line-by-line printing
2. Add highlight logic - prefix selected photo lines with markers
3. Update `worldcup_page.cpp` to call new function
4. Implement tournament bracket - vector of candidates, winner tracking
5. Add round progression - loop until single winner

## Simplifications

- Start with 8 candidates (simpler than 16)
- Use simple text markers for highlighting (not complex borders)
- Assume all ASCII art files have similar heights
- Display photos with fixed column width (~40 chars each)
