#include "word_utils.h"
#include "drawing.h"
#include "helpers.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <ctime>
#include <iostream>

std::string LoadRandomWord(const std::string& path) {
    std::vector<std::string> words;
    std::ifstream reader(path);
    std::string word;
    
    if (reader.is_open()) {
        while (getline(reader, word)) {
            if (!word.empty()) {
                word.erase(remove_if(word.begin(), word.end(), ::isspace), word.end());
                transform(word.begin(), word.end(), word.begin(), ::toupper);
                words.push_back(word);
            }
        }
        reader.close();
    }
    
    if (words.empty()) {
        std::vector<std::string> defaultWords = {"PROGRAMMING", "DEVELOPMENT", "COMPUTER", 
                                     "ALGORITHM", "SOFTWARE", "KEYBOARD", "SCREEN"};
        words = defaultWords;
    }
    
    return words[rand() % words.size()];
}

int CountWrongGuesses(const std::string& word, const std::string& guessed) {
    int errors = 0;
    for (char c : guessed) {
        char upperC = toupper(c);
        if (word.find(upperC) == std::string::npos) {
            errors++;
        }
    }
    return errors;
}

void AddCustomWord() {
    char choice;
    do {
        system("cls");
        PrintMessage("ADD A NEW WORD", true, true, true);
        PrintMessage("Enter a new word to add", false, false);
        PrintMessage("to the dictionary", false, false);
        PrintMessage("(or 0 to cancel):", false, false);
        
        std::string newWord;
        std::cout << "> ";
        std::cin >> newWord;
        
        if (newWord == "0") {
            return;
        }
        
        bool valid = true;
        for (char c : newWord) {
            if (!isalpha(c)) {
                valid = false;
                break;
            }
        }
        
        if (valid && !newWord.empty()) {
            transform(newWord.begin(), newWord.end(), newWord.begin(), ::toupper);
            std::ofstream writer("words.txt", std::ios::app);
            if (writer.is_open()) {
                writer << newWord << std::endl;
                writer.close();
                PrintMessage("Word added successfully!", true, true, true);
            } else {
                PrintMessage("Error opening file", true, true, true);
            }
        } else {
            PrintMessage("Invalid word! (letters only)", true, true, true);
        }
        
        std::cout << "\nAdd another word? (Y/N): ";
        std::cin >> choice;
        choice = toupper(choice);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
    } while (choice == 'Y');
}

int DisplayHelp() {
    system("cls");
    PrintMessage("HANGMAN GAME HELP", true, true, true);
    PrintMessage("Guess the hidden word by", false, false);
    PrintMessage("suggesting letters one by", false, false);
    PrintMessage("one.", false, false);
    PrintMessage("", false, false);
    PrintMessage("You have maximum 10 tries.", false, false);
    PrintMessage("", false, false);
    PrintMessage("Special commands:", false, false);
    PrintMessage("1 - Reveal a letter", false, false);
    PrintMessage("2 - Quit the game", false, false);
    PrintMessage("3 - Add a word", false, true);
    
    std::cout << "\nPress option number: ";
    char choice;
    std::cin >> choice;
    std::cin.ignore();
    
    return (choice == '1' || choice == '2' || choice == '3') ? (choice - '0') : 0;
}