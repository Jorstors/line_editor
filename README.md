# Line Editor Project

This is a command-line line editor project written in C++. The line editor allows users to create, edit, and manipulate lines of text, similar to classic text editors like `ed` or `nano`. It provides a range of editing commands that can be run interactively, making it a simple tool for understanding text manipulation in C++.

## Project Structure

- **`main.cpp`**: Entry point of the program. Manages command-line arguments and initializes the `LineEditor` class.
- **`line_editor.cpp`**: Implements the core line-editing features such as inserting, deleting, modifying, and navigating lines.
- **`file.txt`**: A sample text file used for testing and demonstrating the editor's capabilities.
- **`main.exe`**: Pre-built executable for Windows systems.
- **`for_environment/ledit.cpp`**: Alternate implementation or additional environment-specific code.
- **`for_environment/ledit.exe`**: Pre-built executable for ledit.cpp

## Features

### 1. Text Editing Commands
- **Insert (`i`)**: Insert text at the current line.
- **Append (`a`)**: Append a new line after the current line.
- **Delete (`d`)**: Delete specific lines from the buffer.

### 2. File Handling Commands
- **Write (`w`)**: Save the contents of the buffer to a file.
- **Revert (`r`)**: Revert the buffer to the last saved version.
- **List (`l`)**: List the buffer contents, showing specific line numbers and modified lines.
- **Quit (`q`)**: Exit the editor, with an option to save changes before quitting.

### 3. Navigation
- **Jump (`j`)**: Jump to a specific line number in the buffer.

### Setup

#### Linux/MacOS
1. Clone the repository:
    ```bash
    git clone https://github.com/Jorstors/line_editor.git
    ```
2. Navigate to the project directory:
    ```bash
    cd line_editor
    ```
3. Compile the project:
    ```bash
    g++ -std=c++17 -o line_editor main.cpp line_editor.cpp
    ```
4. Run the editor:
    ```bash
    ./line_editor
    ```

#### Windows
1. Clone the repository:
    ```bash
    git clone https://github.com/Jorstors/line_editor.git
    ```
2. Open `main.exe` to run the pre-built version, or compile using a compatible C++ compiler (e.g., MSVC).

### Commands

- **`i <text>`**: Insert text at the current line.
- **`a <text>`**: Append text after the current line.
- **`d <start_line> [end_line]`**: Delete a single line, range of lines, or selected line.
- **`w [filename]`**: Save the buffer to current or other file.
- **`j <line_number>`**: Jump to a specific line.
- **`l [start_line] [end_line]`**: List the buffer contents, with options to show specific lines.
- **`r`**: Revert to the last saved version.
- **`q`**: Quit the editor, prompting to save if there are unsaved changes.
- **`h`**: Display a help menu.

### Dependencies

- **Linux/MacOS**: Requires a C++17 compatible compiler (e.g., `g++` or `clang++`).
- **Windows**: Pre-built executable (`main.exe`) available, or use a C++17 compatible compiler (e.g., MSVC).

### License

This project is licensed under the ISC License:

Copyright (c) 2024, Justus Jones

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

---

Made by [Justus Jones](https://github.com/Jorstors)
