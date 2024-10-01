#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cctype>
#include <exception>

using namespace std; /* using namespace std for ease of use */

class LineEditor
{
private:
  vector<string> file = {};        // file contents
  string currentFile = "";         // name of current file
  vector<string> buffer = file;    // copy of file for editing
  bool hasBuffer = false;          // if file has been modified
  vector<bool> modifiedLines = {}; // if line has been modified

  int cursor = 1; // cursor/current line

  bool isRunning = true; // editor is running

  // function to print screen
  void printScreen()
  {
    // if cursor is not in buffer, reset cursor
    if (cursor > buffer.size() || cursor < 1)
      cursor = 1;

    // print buffer
    char bufferChar;
    if (!modifiedLines.empty())
      bufferChar = modifiedLines.at(cursor - 1) ? '!' : ' ';
    else
      bufferChar = '\0';
    cout << bufferChar << cursor << "> ";
  }

  // function to update current file
  void updateEditor(string filename)
  {
    // check if same file
    bool isSameFile = currentFile == filename;
    // update filename
    currentFile = filename;
    // reset buffer
    hasBuffer = false;
    // clear file vector
    file.clear();

    // open and read file
    fstream openedFile;
    openedFile.open(filename);
    if (openedFile.is_open())
    {
      string line;
      while (getline(openedFile, line))
      {
        file.push_back(line);
      }
      openedFile.close();
    }
    else
    {
      cout << "Error: File not found" << endl;
      // create file for user
      cout << "Creating file... " << filename << endl;
      fstream newFile;
      newFile.open(filename, ios::out);
      if (newFile.is_open())
      {
        newFile.close();
      }
      else
      {
        newFile.close();
        throw runtime_error("File could not be created");
      }
    }
    // if file is empty, add a blank line
    if (file.empty())
    {
      file.push_back("");
      modifiedLines.push_back(false);
    }

    // update vectors and cursor
    buffer = file;
    modifiedLines.assign(file.size(), false);
    cursor = isSameFile ? cursor : 1;
  }

  void revert(stringstream &arguments)
  {
    if (!hasBuffer)
      return;

    // get confirmation
    cout << "Are you sure you want to revert to the last saved version? (y/n) ";
    char answer;
    cin >> answer;
    cin.ignore();
    if (answer == 'y')
    {
      updateEditor(currentFile);
      cursor = 1;
    }
    else if (answer == 'n')
    {
    }
    else
    {
      cout << "Error: Invalid input" << endl;
    }
  }

  void write(stringstream &arguments)
  {
    // get file from arguments
    string fileInput = "";
    arguments >> fileInput;
    // check if filename is current file
    bool isCurrentFile = false;

    if ((fileInput == currentFile || fileInput == ""))
    {
      if (!hasBuffer)
        return;
      isCurrentFile = true;
    }
    // open file
    fstream openedFile;
    openedFile.open(isCurrentFile ? currentFile : fileInput, ios::out | ios::trunc);
    if (openedFile.is_open())
    {
      // replace current file with buffer contents
      for (const string &line : buffer)
      {
        openedFile << line << endl;
      }
      openedFile.close();

      // update current file if needed
      if (isCurrentFile)
        updateEditor(currentFile);
    }
    else
    {
      cout << "Error: File not found" << endl;
      // create file for user
      cout << "Creating file... " << fileInput << endl;

      fstream newFile;
      newFile.open(fileInput, ios::out);
      if (newFile.is_open())
      {
        for (const string &line : buffer)
        {
          newFile << line << endl;
        }
        newFile.close();
      }
      else
      {
        throw runtime_error("File could not be created.");
        newFile.close();
      }
    }
  }
  void jump(stringstream &arguments)
  {
    int updatedCursor;
    // get line from arguments
    if (!(arguments >> updatedCursor))
      return;

    // check if cursor is valid
    if (updatedCursor == -1)
      cursor = buffer.size();
    else if (updatedCursor < 1 || updatedCursor > buffer.size())
      cout << "Error: Invalid line number" << endl;
    else
      cursor = updatedCursor;
  }
  void insert(stringstream &arguments)
  {
    string stringInput;
    // checking if arguments are valid
    getline(arguments, stringInput);
    // nothing to insert, add new line
    if (stringInput.empty())
    {
      // insert new line at cursor
      buffer.insert(buffer.begin() + cursor - 1, stringInput);
      modifiedLines.insert(modifiedLines.begin() + cursor - 1, true);
    }
    // insert string at cursor, replace current line
    else
    {
      // insert string
      if (!buffer.empty())
        buffer.at(cursor - 1) = stringInput;
      else
        buffer.push_back(stringInput);
      // mark line as modified
      if (!modifiedLines.empty())
        modifiedLines.at(cursor - 1) = true;
      else
        modifiedLines.push_back(true);
    }

    hasBuffer = true;
  }
  void append(stringstream &arguments)
  {
    string stringInput;
    // checking if arguments are valid
    getline(arguments, stringInput);
    // insert new line after cursor
    if (cursor == buffer.size())
    {
      buffer.push_back(stringInput);
      modifiedLines.push_back(true);
    }
    else
    {
      buffer.insert(buffer.begin() + cursor, stringInput);
      modifiedLines.insert(modifiedLines.begin() + cursor, true);
    }
    hasBuffer = true;
  }
  void listBuffer(stringstream &arguments)
  {
    if (buffer.empty())
      return;

    // index variables
    int i = 0;
    int to = buffer.size();

    // checking if there are arguments
    if (!arguments.eof())
    {
      // grabbing arguments
      int firstLine = -255, secondLine = -255;
      arguments >> firstLine >> secondLine;

      // checking if arguments are valid
      if (firstLine != -255 && secondLine == -255) // one argument
      {
        if (firstLine == -1)
          firstLine = buffer.size();
        i = firstLine - 1;
        to = firstLine;
      }
      else if (firstLine != -255 && secondLine != -255) // both arguments
      {
        i = firstLine - 1;

        if (secondLine == -1 || secondLine > buffer.size())
          to = buffer.size();
        else
          to = secondLine;
      }

      // validate arguments are in bounds
      if (i < 0 || to > buffer.size() || to < i)
      {
        cout << "Error: Invalid line numbers" << endl;
        return;
      }
    } //  else - there are no arguments

    cout << "\n";

    for (int j = i; j < to; j++)
    {
      bool modified = modifiedLines.at(j);
      cout << (modified ? "!" : "") << j + 1 << "> " << buffer.at(j) << endl;
    }

    cout << "\n";
  }
  void deleteLine(stringstream &arguments)
  {
    if (buffer.empty())
      return;

    // index variables, default to current line
    int i = cursor - 1;
    int to = cursor;

    // checking if there are arguments
    if (!arguments.eof())
    {
      // grabbing arguments
      int firstLine = -255, secondLine = -255;
      arguments >> firstLine >> secondLine;

      // checking if arguments are valid
      if (firstLine != -255 && secondLine == -255) // one argument
      {
        if (firstLine == -1)
          firstLine = buffer.size();
        i = firstLine - 1;
        to = firstLine;
      }
      else if (firstLine != -255 && secondLine != -255) // both arguments
      {
        i = firstLine - 1;

        if (secondLine == -1 || secondLine > buffer.size())
          to = buffer.size();
        else
          to = secondLine;
      }

      // validate arguments are in bounds
      if (i < 0 || to > buffer.size() || to < i)
      {
        cout << "Error: Invalid line numbers" << endl;
        return;
      }
    } //  else - there are no arguments

    buffer.erase(buffer.begin() + i, buffer.begin() + to);
    modifiedLines.erase(modifiedLines.begin() + i, modifiedLines.begin() + to);

    // if buffer is empty, insert a blank line
    if (buffer.empty())
    {
      buffer.push_back("");
      modifiedLines.push_back(false);
    }

    hasBuffer = true;
  }
  void quitEditor(stringstream &arguments)
  {
    if (hasBuffer)
    {
      cout << "Do you want to save changes? (y/n) ";
      char answer;
      cin >> answer;
      if (answer == 'y')
      {
        stringstream fileInput(currentFile);
        write(fileInput);
      }
      else if (answer == 'n')
      {
      }
      else
      {
        cout << "Error: Invalid input" << endl;
        return;
      }
    }
    isRunning = false;
  }
  void help(stringstream &arguments)
  {
    cout << "\nFunctions:\n";
    cout << "w - Write\n";
    cout << "j - Jump\n";
    cout << "i - Insert\n";
    cout << "a - Append\n";
    cout << "l - List Buffer\n";
    cout << "d - Delete\n";
    cout << "r - Revert\n";
    cout << "q - Quit\n";
    cout << "h - Help\n\n";
  }

public:
  LineEditor() {}

  LineEditor(string filename)
  {
    updateEditor(filename);
  }
  ~LineEditor() {}

  // function to run the editor in a loop
  // there are 8 functions, those being:
  // 1. Write
  // 2. Jump
  // 3. Insert
  // 4. Append
  // 5. List Buffer
  // 6. Delete
  // 7. Quit
  // 8. Help
  bool runEditor()
  {
    // print screen
    printScreen();

    // get input
    string input;
    getline(cin, input);
    stringstream command(input);

    // grabbing first function
    // using stringstream to parse input,
    // and for function arguments
    string commandChar;
    command >> commandChar;

    // checking if command is valid
    if (commandChar.size() != 1)
    {
      cout << "Error: Invalid command" << endl;
      cout << "Type 'h' for help" << endl;
      return isRunning;
    }
    // process input
    switch (tolower(commandChar[0]))
    {
    case 'w':
      write(command);
      break;

    case 'j':
      jump(command);
      break;

    case 'i':
      insert(command);
      break;

    case 'a':
      append(command);
      break;

    case 'l':
      listBuffer(command);
      break;

    case 'd':
      deleteLine(command);
      break;

    case 'r':
      revert(command);
      break;

    case 'q':
      quitEditor(command);
      break;

    case 'h':
      help(command);
      break;

    case '\0':
      break;

    default:
      cout << "Error: Invalid command" << endl;
      cout << "Type 'h' for help" << endl;
      break;
    }

    return isRunning;
  }
};
