# AI Coding Agent Instructions for CPP Repository

## Project Overview
This is a **42 School C++ learning repository** containing introductory C++ exercises following **C++98 standard** with strict compilation flags (`-Wall -Wextra -Werror -std=c++98`). Current focus: object-oriented programming basics with classes and data management.

## Architecture & Key Components

### Directory Structure
- **cpp/cpp0/**: Module 0 - Basic C++ OOP exercises
  - **ex00/**: Simple utility program (string manipulation)
  - **ex01/**: PhoneBook - Contact management system with two classes
    - `Contact`: Data holder for 5 contact fields (name, surname, nickname, login, phone)
    - `PhoneBook`: Container managing up to 8 Contact objects with ADD/SEARCH/EXIT operations

### Data Flow
1. **main.cpp** → Entry point with REPL loop accepting user commands
2. **PhoneBook class** → Command dispatcher (ADD/SEARCH/EXIT)
3. **Contact class** → Storage for individual contact fields via `set_info()`/`get_info()`
4. Static Contact array (`PhoneBooks[8]`) with counter to track filled slots

## Build System & Commands

**Makefile** uses standard 42 pattern:
```bash
cd cpp/cpp0/ex0X/
make        # Compile with C++98 strict flags
make clean  # Remove .o files
make fclean # Remove binary + .o files
make re     # Clean rebuild
```

**Critical flags** (non-negotiable):
- `-Wall -Wextra -Werror -std=c++98` (strict compilation, C++98 only)
- No C++11+ features allowed
- String type: `std::string` (included in headers)

## Code Conventions & Patterns

### Header Format (required)
42-school standard header with metadata (see [PhoneBook.hpp](cpp/cpp0/ex01/PhoneBook.hpp#L1-L9)):
- License notice, creation date, author, update timestamps
- Use `#ifndef` guards with uppercase filename (e.g., `PHONEBOOK_HPP` or `Contact_HPP`)
- Format: `#ifndef FILENAME_HPP` followed by `#define FILENAME_HPP` and closing `#endif`

### Class Structure
- **Public methods**: Command handlers (ADD, SEARCH) and accessors
- **Private data**: Contact arrays and counters
- **Constructors**: Initialize member variables (e.g., `count = 0`)
- **Access pattern**: Private storage + public getter/setter methods (see [Contact class](cpp/cpp0/ex01/Contact.hpp))

### Naming Conventions
- **Class names**: PascalCase (`PhoneBook`, `Contact`)
- **Method names**: UPPERCASE for public commands (`ADD()`, `SEARCH()`)
- **Member access**: Direct assignment to public fields when appropriate (`phonebook.one_field_info = 3` in [main.cpp](cpp/cpp0/ex01/main.cpp#L29))
- **Array fields**: Descriptive names (`PhoneBooks`, `Contact_info`)

### I/O Patterns
- Use `std::getline(std::cin, input)` for string input (handles spaces)
- Output formatting with `std::iomanip` (see [PhoneBook.hpp](cpp/cpp0/ex01/PhoneBook.hpp#L17) includes)
- Use `(void)variable` to suppress unused parameter warnings (see [main.cpp](cpp/cpp0/ex01/main.cpp#L20))

### Error Handling
- **check_enfofile()**: Called in main loop to detect EOF (Ctrl+D) and exit gracefully
- Direct `std::exit(0)` on EOF condition
- No exceptions (C++98 style)

## Integration Points & External Dependencies
- **Standard Library**: `<iostream>`, `<string>`, `<iomanip>`, `<cstdlib>` (no external libraries)
- **No STL containers**: Arrays fixed-size (`Contact[8]`)
- **Manual index management**: PhoneBook tracks count; SEARCH displays indexed list for user selection

## Common Implementation Patterns

### Field Validation
- Contact fields can be set to empty strings; ADD() checks with `.empty()` and re-prompts on validation failure
- PhoneBook tracks entries with modulo arithmetic: `index = count % 8` (circular buffer for 8 max contacts)
- SEARCH validates user-selected indices against actual count

### EOF Handling Pattern
Always call `check_enfofile()` after `std::getline()` in loops. This function:
- Checks `std::cin.eof()` flag
- Prints user-friendly exit message
- Returns 1 on EOF (Ctrl+D), triggering `std::exit(0)` in caller

## When Implementing New Features
1. Maintain 42-school header format with updated timestamps
2. Follow strict compilation without warnings (test immediately: `make clean && make`)
3. Keep C++98 compatibility (no auto, range-for, nullptr, string literals as char*, etc.)
4. Use identical Makefile pattern for new exercises (NAME, SRC, FLAGS variables)
5. For Contact management: store data in Contact; logic in PhoneBook
6. Add EOF checks to all user input loops
7. Test with: `make clean && make && make re` to catch compilation issues early
