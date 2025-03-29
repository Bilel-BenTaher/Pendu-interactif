#include "hangman.h"
#include "drawing.h"
#include "word_utils.h"
#include "helpers.h"
#include <iostream>
#include <string>
#include <cstdlib>  // Pour exit()

/**
 * @brief Fonction principale du jeu du pendu
 * 
 * Gère le déroulement complet d'une partie de pendu :
 * - Initialisation des variables
 * - Boucle de jeu principale
 * - Gestion des entrées utilisateur
 * - Affichage des résultats
 */
void PlayGame() {
    std::string guessedLetters;  // Lettres déjà proposées
    std::string wordToGuess = LoadRandomWord("words.txt");  // Mot à deviner
    int tries = 0;  // Nombre d'essais incorrects
    bool win = false;  // Indicateur de victoire
    char input;  // Saisie utilisateur

    // Boucle principale du jeu
    do {
        system("cls");  // Efface la console
        
        // Affichage de l'interface
        PrintMessage("HANGMAN GAME", true, true, true);  // Titre
        PrintMessage("Remaining tries: " + std::to_string(10 - tries), false, false, false);  // Compteur
        DrawHangman(tries);  // Dessin du pendu
        PrintAvailableLetters(guessedLetters, wordToGuess);  // Lettres disponibles
        PrintMessage("Guess the word", false, false, true);  // Invite
        win = PrintWordAndCheckWin(wordToGuess, guessedLetters);  // Mot à deviner

        if (win) break;  // Sortie si victoire

        // Menu des options
        PrintMessage("1:Help, 2:Exit, 3:Add word", false, true, false);
        std::cout << "> ";  // Prompt de saisie
        
        // Récupération de l'entrée utilisateur
        std::cin >> input;
        std::cin.ignore();

        // Gestion des options du menu
        if (input == '1') {  // Menu d'aide
            int helpChoice = DisplayHelp();
            if (helpChoice == 1) {
                // Révéler une lettre aléatoire non découverte
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
                // Ajouter un mot personnalisé
                AddCustomWord();
            }
            continue;
        }
        else if (input == '2') {  // Quitter directement
            PrintMessage("GAME ABORTED", true, true, true);
            exit(0);
        }
        else if (input == '3') {  // Ajouter un mot
            AddCustomWord();
            continue;
        }

        // Traitement d'une lettre devinée
        input = toupper(input);  // Normalisation en majuscule

        // Validation de la saisie
        if (!isalpha(input)) {
            PrintMessage("Enter a valid letter!", true, true, true);
            std::cout << "\nPress any key to continue...";
            std::cin.get();
            continue;
        }

        // Vérification si la lettre a déjà été proposée
        if (guessedLetters.find(input) != std::string::npos) {
            PrintMessage("Letter already used!", true, true, true);
            std::cout << "\nPress any key to continue...";
            std::cin.get();
            continue;
        }

        // Ajout de la nouvelle lettre et mise à jour du compteur
        guessedLetters += input;
        tries = CountWrongGuesses(wordToGuess, guessedLetters);

    } while (tries < 10);  // Condition de défaite (10 essais max)

    // Affichage du résultat final
    if (win) {
        PrintMessage("CONGRATULATIONS! YOU WON!", true, true, true);
        PrintMessage("The word was: " + wordToGuess, true, true, false);
    } else {
        PrintMessage("GAME OVER - YOU LOST", true, true, true);
        PrintMessage("The word was: " + wordToGuess, true, true, false);
    }
}