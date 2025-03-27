#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <limits>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

using namespace std;

namespace HangmanColors {
#ifdef _WIN32
    const int DEFAULT = 7;
    const int TITLE = 11;
    const int CORRECT = 10;
    const int WRONG = 12;
    const int HIGHLIGHT = 14;
#else
    const string DEFAULT = "\033[0m";
    const string TITLE = "\033[1;33m";
    const string CORRECT = "\033[1;32m";
    const string WRONG = "\033[1;31m";
    const string HIGHLIGHT = "\033[1;36m";
#endif
}

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
    cout << HangmanColors::DEFAULT;
#endif
}

void PrintMessage(const string& message, bool printTop = true, bool printBottom = true, bool isTitle = false) {
    if (isTitle) {
#ifdef _WIN32
        SetConsoleColor(HangmanColors::TITLE);
#else
        cout << HangmanColors::TITLE;
#endif
    }

    if (printTop) {
        cout << "+---------------------------------+\n";
        cout << "|";
    } else {
        cout << "|";
    }

    bool front = true;
    string formatted = message;
    for (int i = message.length(); i < 33; i++) {
        formatted = front ? " " + formatted : formatted + " ";
        front = !front;
    }

    cout << formatted;

    if (printBottom) {
        cout << "|\n";
        cout << "+---------------------------------+\n";
    } else {
        cout << "|\n";
    }

    ResetConsoleColor();
}

void DrawHangman(int guessCount = 0) {
    PrintMessage("", false, false);
    
    vector<string> hangmanDrawing = {
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
    cout << (guessCount > 0 ? HangmanColors::WRONG : HangmanColors::DEFAULT);
#endif

    for (const auto& line : hangmanDrawing) {
        PrintMessage(line, false, false);
    }
    
    ResetConsoleColor();
}

void PrintLetters(const string& input, char from, char to, const string& word) {
    string s;
    for (char i = from; i <= to; i++) {
        char upperChar = toupper(i);
        if (input.find(upperChar) == string::npos) {
            s += i;
            s += " ";
        } else {
            bool isInWord = (word.find(upperChar) != string::npos);
#ifdef _WIN32
            SetConsoleColor(isInWord ? HangmanColors::CORRECT : HangmanColors::WRONG);
#else
            cout << (isInWord ? HangmanColors::CORRECT : HangmanColors::WRONG);
#endif
            s += i;
            s += " ";
            ResetConsoleColor();
        }
    }
    PrintMessage(s, false, false);
}

void PrintAvailableLetters(const string& guessed, const string& word) {
    PrintMessage("AVAILABLE LETTERS", true, true, true);
    PrintLetters(guessed, 'A', 'M', word);
    PrintLetters(guessed, 'N', 'Z', word);
}

bool PrintWordAndCheckWin(const string& word, const string& guessed) {
    bool won = true;
    string s;
    for (char c : word) {
        char upperC = toupper(c);
        if (guessed.find(upperC) == string::npos) {
            won = false;
            s += "_ ";
        } else {
#ifdef _WIN32
            SetConsoleColor(HangmanColors::CORRECT);
#else
            cout << HangmanColors::CORRECT;
#endif
            s += c;
            s += " ";
            ResetConsoleColor();
        }
    }
    PrintMessage(s, false);
    return won;
}

string LoadRandomWord(const string& path) {
    vector<string> words;
    ifstream reader(path);
    string word;
    
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
        vector<string> defaultWords = {"PROGRAMMING", "DEVELOPMENT", "COMPUTER", 
                                     "ALGORITHM", "SOFTWARE", "KEYBOARD", "SCREEN"};
        words = defaultWords;
    }
    
    return words[rand() % words.size()];
}

int CountWrongGuesses(const string& word, const string& guessed) {
    int errors = 0;
    for (char c : guessed) {
        char upperC = toupper(c);
        if (word.find(upperC) == string::npos) {
            errors++;
        }
    }
    return errors;
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
    
    cout << "\nPress option number: ";
    char choice;
    cin >> choice;
    cin.ignore();
    
    // Retourne le choix numérique (1, 2 ou 3) ou 0 pour retourner au jeu
    return (choice == '1' || choice == '2' || choice == '3') ? (choice - '0') : 0;
}

void AddCustomWord() {
    char choice;
    do {
        system("cls");
        PrintMessage("ADD A NEW WORD", true, true, true);
        PrintMessage("Enter a new word to add", false, false);
        PrintMessage("to the dictionary", false, false);
        PrintMessage("(or 0 to cancel):", false, false);
        
        string newWord;
        cout << "> ";
        cin >> newWord;
        
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
            ofstream writer("words.txt", ios::app);
            if (writer.is_open()) {
                writer << newWord << endl;
                writer.close();
                PrintMessage("Word added successfully!", true, true, true);
            } else {
                PrintMessage("Error opening file", true, true, true);
            }
        } else {
            PrintMessage("Invalid word! (letters only)", true, true, true);
        }
        
        cout << "\nAdd another word? (Y/N): ";
        cin >> choice;
        choice = toupper(choice);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
    } while (choice == 'Y');
}

void PlayGame() {
    string guessedLetters;
    string wordToGuess = LoadRandomWord("words.txt");
    int tries = 0;
    bool win = false;
    char input;

    do {
        system("cls"); 
        PrintMessage("HANGMAN GAME", true, true, true);
        PrintMessage("Remaining tries: " + to_string(10 - tries), false, false);
        DrawHangman(tries);
        PrintAvailableLetters(guessedLetters, wordToGuess);
        PrintMessage("Guess the word", false, false, true);
        win = PrintWordAndCheckWin(wordToGuess, guessedLetters);

        if (win) break;

        PrintMessage("1:Help, 2:Exit, 3:Add word", false, true);
        cout << "> ";
        
        cin >> input;
        cin.ignore();

        if (input == '1') {
            int helpChoice = DisplayHelp();
            if (helpChoice == 1) {
                // Révéler une lettre
                for (char c : wordToGuess) {
                    char upperC = toupper(c);
                    if (guessedLetters.find(upperC) == string::npos) {
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
            // Si helpChoice == 0, on continue simplement le jeu
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
            cout << "\nPress any key to continue...";
            cin.get();
            continue;
        }

        if (guessedLetters.find(input) != string::npos) {
            PrintMessage("Letter already used!", true, true, true);
            cout << "\nPress any key to continue...";
            cin.get();
            continue;
        }

        guessedLetters += input;
        tries = CountWrongGuesses(wordToGuess, guessedLetters);

    } while (tries < 10);

    if (win) {
        PrintMessage("CONGRATULATIONS! YOU WON!", true, true, true);
        PrintMessage("The word was: " + wordToGuess, true, true, true);
    } else {
        PrintMessage("GAME OVER - YOU LOST", true, true, true);
        PrintMessage("The word was: " + wordToGuess, true, true, true);
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    char playAgain;
    
    do {
        PlayGame();
        
        cout << "\nDo you want to play again? (Y/N): ";
        cin >> playAgain;
        playAgain = toupper(playAgain);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
    } while (playAgain == 'Y');

    return 0;
}