#include "helpers.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

void SetConsoleColor(int colorCode) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
#endif
}

void ResetConsoleColor() {
#ifdef _WIN32
    SetConsoleColor(HangmanColors::DEFAULT);
#else
    std::cout << HangmanColors::DEFAULT;
#endif
}

void PrintMessage(const std::string& message, bool printTop, bool printBottom, bool isTitle) {
    if (isTitle) {
#ifdef _WIN32
        SetConsoleColor(HangmanColors::TITLE);
#else
        std::cout << HangmanColors::TITLE;
#endif
    }

    if (printTop) {
        std::cout << "+---------------------------------+\n";
        std::cout << "|";
    } else {
        std::cout << "|";
    }

    bool front = true;
    std::string formatted = message;
    for (int i = message.length(); i < 33; i++) {
        formatted = front ? " " + formatted : formatted + " ";
        front = !front;
    }

    std::cout << formatted;

    if (printBottom) {
        std::cout << "|\n";
        std::cout << "+---------------------------------+\n";
    } else {
        std::cout << "|\n";
    }

    ResetConsoleColor();
}