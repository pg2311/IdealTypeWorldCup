# Refactoring Plan for Ideal Type World Cup

## Analysis Summary

This codebase is a functional console-based "Ideal Type World Cup" game. While it works, there are several code quality issues that should be addressed:

### Current Issues Identified:

1. **Magic numbers scattered throughout the code** (hardcoded values like 8, 37, trim values)
2. **Massive code duplication** in `photo.cpp` (file reading logic repeated)
3. **Unsafe C-style code** (sprintf, char arrays, suppressed security warnings)
4. **Poor separation of concerns** (display + business logic mixed)
5. **Global mutable state** (names array)
6. **Inconsistent naming conventions** (printphoto vs printPhotoSideBySide)
7. **Weak type safety** (int instead of enums for gender/selection)
8. **No centralized constants** (values scattered across files)
9. **Missing error handling** (file operations can fail silently)
10. **Code organization issues** (tight coupling, no abstractions)

---

## Refactoring Todo List

### Phase 1: Essential Fixes (Easy & High Impact)

#### 1.1 Create Constants Header
**File:** Create `constants.h`
**Priority:** HIGH
**Complexity:** EASY

- [ ] Create `constants.h` with all magic numbers
- [ ] Define photo-related constants (PHOTO_START_MALE=1, PHOTO_START_FEMALE=9, PHOTOS_PER_GENDER=8)
- [ ] Define display constants (TRIM_LEFT=8, TRIM_RIGHT=8, MAX_HEIGHT=37, SKIP_TOP=8)
- [ ] Define array size constants (MAX_NAMES=20, MAX_NAME_LENGTH=100)
- [ ] Include in all relevant files and replace magic numbers

**Benefits:** Makes code self-documenting, easier to modify values, reduces errors

---

#### 1.2 Replace int with Enums for Type Safety
**Files:** `start_page.h`, `settings_page.h`, `worldcup_page.h`, `main.cpp`
**Priority:** HIGH
**Complexity:** EASY

- [ ] Create `Gender` enum class (MALE=0, FEMALE=1)
- [ ] Create `MenuChoice` enum class (START=0, EXIT=1)
- [ ] Update function signatures to use enum types instead of int
- [ ] Update all usages in main.cpp and page files

**Benefits:** Type safety, self-documenting code, prevents invalid values

---

#### 1.3 Fix Inconsistent Naming
**Files:** `photo.cpp`, `photo.h`
**Priority:** MEDIUM
**Complexity:** EASY

- [ ] Rename `printphoto` to `printPhoto` (camelCase consistency)
- [ ] Consider renaming display functions to use consistent verbs (show vs display)

**Benefits:** Code consistency, readability

---

#### 1.4 Remove Unsafe C-Style Code
**Files:** `photo.cpp`
**Priority:** HIGH
**Complexity:** EASY

- [ ] Replace `sprintf(path, "imgs/%d.txt", photo_no)` with `std::string` or `std::ostringstream`
- [ ] Replace `char path[256]` with `std::string path`
- [ ] Remove `#define _CRT_SECURE_NO_WARNINGS` after fixing sprintf

**Benefits:** Memory safety, modern C++ practices, removes security warnings

---

### Phase 2: Code Quality Improvements (Medium Complexity)

#### 2.1 Extract File Reading into Separate Function
**File:** `photo.cpp`
**Priority:** HIGH
**Complexity:** MEDIUM

- [ ] Create helper function: `std::vector<std::wstring> readPhotoFile(int photo_no)`
- [ ] Refactor `printphoto` to use the helper
- [ ] Refactor `printPhotoSideBySide` to use the helper
- [ ] Add error handling for file not found

**Benefits:** Eliminates 100+ lines of code duplication, easier to maintain

---

#### 2.2 Extract Dimension Calculation Logic
**File:** `photo.cpp`
**Priority:** MEDIUM
**Complexity:** MEDIUM

- [ ] Create `struct PhotoDimensions { size_t width; size_t height; }`
- [ ] Create function: `PhotoDimensions calculateDimensions(const vector<wstring>& lines, int trim_left, int trim_right)`
- [ ] Refactor both print functions to use it

**Benefits:** Reduces duplication, clearer separation of concerns

---

#### 2.3 Move Names to Data File or Config
**Files:** `photo.cpp`, new `names.txt` or `config.cpp`
**Priority:** MEDIUM
**Complexity:** MEDIUM

- [ ] Create `names.txt` or similar data file with names
- [ ] Create function to load names at startup
- [ ] Remove hardcoded names array from photo.cpp
- [ ] Consider creating a `Candidate` struct with {id, name, photo_path}

**Benefits:** Easier to add/modify names without recompiling, better data/code separation

---

#### 2.4 Add Error Handling
**Files:** `photo.cpp`, all page files
**Priority:** HIGH
**Complexity:** MEDIUM

- [ ] Add error handling in `readPhotoFile` for missing files
- [ ] Display error message if photo file not found
- [ ] Validate photo numbers before accessing names array
- [ ] Add boundary checks for array accesses

**Benefits:** Prevents crashes, better user experience, more robust application

---

### Phase 3: Architecture Improvements (Higher Complexity)

#### 3.1 Create Photo Class/Module
**Files:** New `photo_manager.cpp/h`, refactor `photo.cpp`
**Priority:** MEDIUM
**Complexity:** HIGH

- [ ] Create `PhotoManager` class to encapsulate photo operations
- [ ] Move file reading, caching logic into class
- [ ] Consider caching loaded photos to avoid re-reading
- [ ] Update all callers to use new interface

**Benefits:** Better encapsulation, potential performance improvement, easier testing

---

#### 3.2 Separate Display from Business Logic
**Files:** All page files
**Priority:** MEDIUM
**Complexity:** HIGH

- [ ] Extract display functions into separate display module
- [ ] Keep business logic (state management, navigation) in page modules
- [ ] Create clear interfaces between layers

**Benefits:** Easier to test, clearer separation of concerns, easier to modify UI

---

#### 3.3 Create Tournament/Game Logic Module
**File:** New `tournament.cpp/h`, refactor `worldcup_page.cpp`
**Priority:** LOW
**Complexity:** HIGH

- [ ] Extract tournament bracket logic into separate module
- [ ] Create data structures for tournament state
- [ ] Separate UI from game logic
- [ ] Make tournament logic reusable and testable

**Benefits:** Testable game logic, potential for different tournament formats

---

### Phase 4: Optional Enhancements

#### 4.1 Add Randomization
**File:** `worldcup_page.cpp`
**Priority:** LOW
**Complexity:** EASY

- [ ] Add `<random>` header
- [ ] Shuffle candidates at start of tournament
- [ ] Note: This addresses TODO comment in original code

**Benefits:** Better gameplay variety

---

#### 4.2 Add Configuration System
**Files:** New `config.cpp/h`
**Priority:** LOW
**Complexity:** MEDIUM

- [ ] Create config file for display settings
- [ ] Load trim values, dimensions from config
- [ ] Allow customization without recompiling

**Benefits:** Easier customization, flexibility

---

#### 4.3 Improve Console Output
**Files:** `input.cpp`, display functions
**Priority:** LOW
**Complexity:** MEDIUM

- [ ] Replace `system("cls")` with ANSI escape codes or Windows API
- [ ] Add color support
- [ ] Improve visual presentation

**Benefits:** Better user experience, more portable code

---

## Recommended Execution Order

Start with Phase 1 in order (1.1 → 1.2 → 1.3 → 1.4), then proceed to Phase 2. Each task in Phase 1 is relatively independent and provides immediate benefit.

**Quick wins:** 1.1 (constants), 1.2 (enums), 1.4 (remove sprintf) can be done quickly with high impact.

**Biggest impact:** 2.1 (extract file reading) eliminates the most code duplication and improves maintainability significantly.

---

## Notes

- Each phase builds upon previous phases
- After Phase 1, the code will be significantly more maintainable
- Phase 2 focuses on reducing duplication (the biggest code smell currently)
- Phase 3 is optional but would make the codebase more professional
- All changes should maintain backward compatibility in functionality
- Test after each change to ensure nothing breaks
