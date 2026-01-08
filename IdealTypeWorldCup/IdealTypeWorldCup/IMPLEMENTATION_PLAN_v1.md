# Implementation Plan: Side-by-Side Photo Display with Tournament

## Current State
- `printphoto()` displays a single ASCII art photo from a file
- `worldcup_page.cpp` shows one photo at a time
- Navigation works but only highlights text names
- No tournament bracket system

## Required Changes

### 1. Photo Display Module (`photo.cpp/h`)

**New function: `printPhotoSideBySide(int left_photo, int right_photo, int selected)`**
- Load both photo files into memory (vectors of strings)
- Display them side-by-side:
  - Split console width in half
  - Print left photo on left side, right photo on right side
  - Add visual separator between them
- Highlight selected photo:
  - Add border characters (like `>>` or `**`) around selected photo
  - OR use different brackets/markers

**Implementation approach:**
1. Read both files into `vector<string>`
2. Iterate through lines
3. For each line: print left photo line + separator + right photo line
4. Add highlight markers based on `selected` parameter

### 2. World Cup Page (`worldcup_page.cpp`)

**Tournament bracket structure:**
- Track multiple rounds (16→8→4→2→1)
- Store candidate indices in array/vector
- After each match, winner advances to next round

**Match flow:**
1. Display two candidates side-by-side with `printPhotoSideBySide()`
2. User navigates left/right (updates `selected`)
3. User presses Enter → record winner
4. Move to next match in current round
5. When round complete → advance to next round
6. Repeat until final winner

**Data structure needed:**
```cpp
vector<int> current_round;  // Photo indices in current round
vector<int> next_round;      // Winners advance here
int match_index;             // Current match in round
```

**Main loop changes:**
- Replace single match with tournament loop
- Track rounds and matches
- Display round info (e.g., "Round of 16", "Quarter Finals")

### 3. Settings Page Integration

- Gender selection determines starting photo indices:
  - Male: photos 0-7 (8 candidates)
  - Female: photos 8-15 (8 candidates)
- Initialize `current_round` with appropriate indices

## Technical Considerations

**Console width:**
- Standard console is ~80 characters wide
- Each photo column: ~35 characters
- Separator: ~10 characters
- May need to check actual photo width

**File reading:**
- Current `printphoto()` reads file every time
- Side-by-side needs both files in memory
- Consider caching or reading once

**Highlighting:**
- Option 1: Add `>>> ` prefix to selected photo lines
- Option 2: Draw box border around selected photo
- Option 3: Use different characters (*, #, etc.)

## Implementation Steps

1. Add `printPhotoSideBySide()` function to `photo.cpp/h`
2. Test side-by-side display with hardcoded photos
3. Add highlighting for selected photo
4. Implement tournament bracket in `worldcup_page.cpp`:
   - Initialize with 8 candidates
   - Loop through matches
   - Track winners
5. Add round display (show which round user is in)
6. Handle final winner display

## Edge Cases

- What if ASCII art files have different heights?
- What if console is too narrow?
- Handle file read errors gracefully
- Ensure proper alignment of photo columns
