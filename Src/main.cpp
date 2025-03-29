// main.cpp - Point d'entrée principal du jeu Hangman

#include "hangman.h"
#include <ctime>
#include <limits>
#include <iostream>

int main() {
    // Initialisation du générateur de nombres aléatoires
    srand(static_cast<unsigned int>(time(nullptr)));
    
    char playAgain;
    
    do {
        // Lancement d'une partie
        PlayGame();
        
        // Demander si le joueur veut rejouer
        std::cout << "\nDo you want to play again? (Y/N): ";
        std::cin >> playAgain;
        playAgain = toupper(playAgain);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
    } while (playAgain == 'Y');

    return 0;
}