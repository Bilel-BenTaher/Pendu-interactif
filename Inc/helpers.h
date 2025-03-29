#ifndef HELPERS_H
#define HELPERS_H

#include <string>

namespace HangmanColors {
#ifdef _WIN32
    const int DEFAULT = 7;
    const int TITLE = 11;
    const int CORRECT = 10;
    const int WRONG = 12;
    const int HIGHLIGHT = 14;
#else
    const std::string DEFAULT = "\033[0m";
    const std::string TITLE = "\033[1;33m";
    const std::string CORRECT = "\033[1;32m";
    const std::string WRONG = "\033[1;31m";
    const std::string HIGHLIGHT = "\033[1;36m";
#endif
}

void SetConsoleColor(int colorCode);
void ResetConsoleColor();
void PrintMessage(const std::string& message, bool printTop = true, bool printBottom = true, bool isTitle = false);

#endif