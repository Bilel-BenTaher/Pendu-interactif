#include "drawing.h"
#include "helpers.h"
#include <vector>
#include <algorithm>
#include <cctype>

void DrawHangman(int guessCount) {
    PrintMessage("", false, false, false);
    
    std::vector<std::string> hangmanDrawing = {
        " +---+   ",
        guessCount >= 1 ? " |   |   " : "     |   ",
        guessCount >= 3 ? " O   |   " : (guessCount >= 1 ? "     |   " : "         "),
        guessCount >= 6 ? "/|\\  |   " : 
            (guessCount >= 5 ? "/|   |   " : 
            (guessCount >= 4 ? "/     |   " : "      |   ")),
        guessCount >= 7 ? " |   |   " : "     |   ",
        guessCount >= 9 ? "/ \\  |___" : 
            (guessCount >= 8 ? "/     |___" : "      |___")
    };

#ifdef _WIN32
    SetConsoleColor(guessCount > 0 ? HangmanColors::WRONG : HangmanColors::DEFAULT);
#else
    std::cout << (guessCount > 0 ? HangmanColors::WRONG : HangmanColors::DEFAULT);
#endif

    for (const auto& line : hangmanDrawing) {
        PrintMessage(line, false, false, false);
    }
    
    ResetConsoleColor();
}

void PrintLetters(const std::string& input, char from, char to, const std::string& word) {
    std::string s;
    for (char i = from; i <= to; i++) {
        char upperChar = toupper(i);
        if (input.find(upperChar) == std::string::npos) {
            s += i;
            s += " ";
        } else {
            bool isInWord = (word.find(upperChar) != std::string::npos);
#ifdef _WIN32
            SetConsoleColor(isInWord ? HangmanColors::CORRECT : HangmanColors::WRONG);
#else
            std::cout << (isInWord ? HangmanColors::CORRECT : HangmanColors::WRONG);
#endif
            s += i;
            s += " ";
            ResetConsoleColor();
        }
    }
    PrintMessage(s, false, false, false);
}

void PrintAvailableLetters(const std::string& guessed, const std::string& word) {
    PrintMessage("AVAILABLE LETTERS", true, true, true);
    PrintLetters(guessed, 'A', 'M', word);
    PrintLetters(guessed, 'N', 'Z', word);
}

bool PrintWordAndCheckWin(const std::string& word, const std::string& guessed) {
    bool won = true;
    std::string s;
    for (char c : word) {
        char upperC = toupper(c);
        if (guessed.find(upperC) == std::string::npos) {
            won = false;
            s += "_ ";
        } else {
#ifdef _WIN32
            SetConsoleColor(HangmanColors::CORRECT);
#else
            std::cout << HangmanColors::CORRECT;
#endif
            s += c;
            s += " ";
            ResetConsoleColor();
        }
    }
    PrintMessage(s, false, true, false);
    return won;
}