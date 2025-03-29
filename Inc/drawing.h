#ifndef DRAWING_H
#define DRAWING_H

#include <string>

void DrawHangman(int guessCount = 0);
void PrintAvailableLetters(const std::string& guessed, const std::string& word);
bool PrintWordAndCheckWin(const std::string& word, const std::string& guessed);
void PrintMessage(const std::string& message, bool printTop, bool printBottom, bool isTitle);
void PrintLetters(const std::string& input, char from, char to, const std::string& word);

#endif