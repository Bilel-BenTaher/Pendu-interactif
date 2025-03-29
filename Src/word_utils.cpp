#include "word_utils.h"
#include "drawing.h"
#include "helpers.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <ctime>
#include <iostream>

/**
 * @brief Charge un mot aléatoire depuis un fichier
 * @param path Chemin vers le fichier contenant les mots
 * @return Un mot sélectionné aléatoirement
 * 
 * Lit un fichier texte contenant un mot par ligne, nettoie et met en majuscules chaque mot.
 * Si le fichier est vide ou inaccessible, utilise une liste de mots par défaut.
 */
std::string LoadRandomWord(const std::string& path) {
    std::vector<std::string> words;  // Vecteur pour stocker les mots lus
    std::ifstream reader(path);      // Flux de lecture du fichier
    std::string word;                // Variable temporaire pour chaque mot
    
    // Lecture du fichier
    if (reader.is_open()) {
        while (getline(reader, word)) {
            if (!word.empty()) {
                // Nettoyage du mot : suppression des espaces et mise en majuscules
                word.erase(remove_if(word.begin(), word.end(), ::isspace), word.end());
                transform(word.begin(), word.end(), word.begin(), ::toupper);
                words.push_back(word);
            }
        }
        reader.close();
    }
    
    // Si aucun mot n'a été trouvé, utiliser une liste par défaut
    if (words.empty()) {
        std::vector<std::string> defaultWords = {"PROGRAMMING", "DEVELOPMENT", "COMPUTER", 
                                     "ALGORITHM", "SOFTWARE", "KEYBOARD", "SCREEN"};
        words = defaultWords;
    }
    
    // Retourne un mot aléatoire du vecteur
    return words[rand() % words.size()];
}

/**
 * @brief Compte le nombre de mauvaises lettres devinées
 * @param word Le mot à deviner
 * @param guessed Les lettres déjà proposées
 * @return Le nombre de lettres incorrectes
 * 
 * Parcourt toutes les lettres devinées et compte celles qui ne sont pas dans le mot.
 */
int CountWrongGuesses(const std::string& word, const std::string& guessed) {
    int errors = 0;  // Compteur d'erreurs
    
    for (char c : guessed) {
        char upperC = toupper(c);
        if (word.find(upperC) == std::string::npos) {
            errors++;  // Incrémente si la lettre n'est pas dans le mot
        }
    }
    return errors;
}

/**
 * @brief Permet d'ajouter un mot personnalisé au dictionnaire
 * 
 * Affiche une interface pour saisir un nouveau mot, le valide
 * (lettres uniquement, non vide) et l'ajoute au fichier words.txt.
 * Propose de continuer à ajouter des mots après chaque ajout.
 */
void AddCustomWord() {
    char choice;
    do {
        system("cls");  // Efface la console
        
        // Affichage des instructions
        PrintMessage("ADD A NEW WORD", true, true, true);
        PrintMessage("Enter a new word to add", false, false);
        PrintMessage("to the dictionary", false, false);
        PrintMessage("(or 0 to cancel):", false, false);
        
        // Saisie utilisateur
        std::string newWord;
        std::cout << "> ";
        std::cin >> newWord;
        
        // Option d'annulation
        if (newWord == "0") {
            return;
        }
        
        // Validation du mot (lettres uniquement)
        bool valid = true;
        for (char c : newWord) {
            if (!isalpha(c)) {
                valid = false;
                break;
            }
        }
        
        // Si le mot est valide, on l'ajoute au fichier
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
        
        // Demande si l'utilisateur veut ajouter un autre mot
        std::cout << "\nAdd another word? (Y/N): ";
        std::cin >> choice;
        choice = toupper(choice);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
    } while (choice == 'Y');  // Continue tant que l'utilisateur répond 'Y'
}

/**
 * @brief Affiche l'aide du jeu et les options spéciales
 * @return Le choix de l'utilisateur (1, 2 ou 3) ou 0 pour un choix invalide
 * 
 * Affiche les règles du jeu et les commandes spéciales disponibles.
 * Attend que l'utilisateur sélectionne une option et la retourne.
 */
int DisplayHelp() {
    system("cls");  // Efface la console
    
    // Affichage des informations d'aide
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
    
    // Saisie du choix utilisateur
    std::cout << "\nPress option number: ";
    char choice;
    std::cin >> choice;
    std::cin.ignore();
    
    // Retourne le choix numérique ou 0 si invalide
    return (choice == '1' || choice == '2' || choice == '3') ? (choice - '0') : 0;
}