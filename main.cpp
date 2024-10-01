#include "line_editor.cpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cctype>

int main(int argc, char *argv[])
{
  try // catch any exceptions
  {
    LineEditor editor;

    // If file is not argued, ask for it
    if (argc < 2)
    {
      cout << "Error: File not entered, please enter a file:\n> ";
      string filename;
      cin >> filename;
      // eat newline
      cin.ignore();
      // create file for user
      editor = LineEditor(filename);
    }
    // file has been argued
    else
    {
      string filename = argv[1];
      editor = LineEditor(filename);
    }
    while (editor.runEditor())
    {
    }
  }
  catch (const exception &e)
  {
    cerr << "Quit: " << e.what() << endl;
  }
  return 0;
}