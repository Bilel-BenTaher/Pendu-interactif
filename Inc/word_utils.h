#ifndef WORD_UTILS_H
#define WORD_UTILS_H

#include <string>

std::string LoadRandomWord(const std::string& path);
int CountWrongGuesses(const std::string& word, const std::string& guessed);
void AddCustomWord();
int DisplayHelp();

#endif