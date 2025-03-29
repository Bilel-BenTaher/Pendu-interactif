#include "hangman.h"
#include "drawing.h"
#include "word_utils.h"
#include "helpers.h"
#include <iostream>
#include <string>
#include <cstdlib>  // Pour exit()

void PlayGame() {
    std::string guessedLetters;
    std::string wordToGuess = LoadRandomWord("words.txt");
    int tries = 0;
    bool win = false;
    char input;

    do {
        system("cls"); 
        PrintMessage("HANGMAN GAME", true, true, true);
        PrintMessage("Remaining tries: " + std::to_string(10 - tries), false, false, false);
        DrawHangman(tries);
        PrintAvailableLetters(guessedLetters, wordToGuess);
        PrintMessage("Guess the word", false, false, true);
        win = PrintWordAndCheckWin(wordToGuess, guessedLetters);

        if (win) break;

        PrintMessage("1:Help, 2:Exit, 3:Add word", false, true, false);
        std::cout << "> ";
        
        std::cin >> input;
        std::cin.ignore();

        if (input == '1') {
            int helpChoice = DisplayHelp();
            if (helpChoice == 1) {
                // Révéler une lettre
                for (char c : wordToGuess) {
                    char upperC = toupper(c);
                    if (guessedLetters.find(upperC) == std::string::npos) {
                        guessedLetters += upperC;
                        break;
                    }
                }
            }
            else if (helpChoice == 2) {
                // Quitter le jeu
                PrintMessage("GAME ABORTED", true, true, true);
                exit(0);
            }
            else if (helpChoice == 3) {
                // Ajouter un mot
                AddCustomWord();
            }
            continue;
        }
        else if (input == '2') {
            PrintMessage("GAME ABORTED", true, true, true);
            exit(0);
        }
        else if (input == '3') {
            AddCustomWord();
            continue;
        }

        input = toupper(input);

        if (!isalpha(input)) {
            PrintMessage("Enter a valid letter!", true, true, true);
            std::cout << "\nPress any key to continue...";
            std::cin.get();
            continue;
        }

        if (guessedLetters.find(input) != std::string::npos) {
            PrintMessage("Letter already used!", true, true, true);
            std::cout << "\nPress any key to continue...";
            std::cin.get();
            continue;
        }

        guessedLetters += input;
        tries = CountWrongGuesses(wordToGuess, guessedLetters);

    } while (tries < 10);

    if (win) {
        PrintMessage("CONGRATULATIONS! YOU WON!", true, true, true);
        PrintMessage("The word was: " + wordToGuess, true, true, false);
    } else {
        PrintMessage("GAME OVER - YOU LOST", true, true, true);
        PrintMessage("The word was: " + wordToGuess, true, true, false);
    }
}