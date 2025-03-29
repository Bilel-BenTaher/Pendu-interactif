#include "hangman.h"  // Inclut le header principal du jeu
#include <ctime>      // Pour time()
#include <limits>     // Pour numeric_limits
#include <iostream>   // Pour les entrées/sorties

/**
 * @brief Point d'entrée principal du programme
 * 
 * Gère le cycle complet du jeu :
 * 1. Initialisation du générateur aléatoire
 * 2. Boucle principale du jeu
 * 3. Gestion des parties multiples
 * 
 * @return int Code de sortie (0 pour une exécution réussie)
 */
int main() {
    // Initialise le générateur de nombres aléatoires avec l'heure actuelle
    // comme graine pour la sélection aléatoire des mots
    srand(static_cast<unsigned int>(time(nullptr)));
    
    char playAgain;  // Stocke le choix de l'utilisateur pour rejouer
    
    do {
        // =============================================
        // LANCEMENT D'UNE PARTIE
        // =============================================
        PlayGame();  // Appel de la fonction principale du jeu
        
        // =============================================
        // DEMANDE DE REJOUER
        // =============================================
        std::cout << "\nDo you want to play again? (Y/N): ";
        std::cin >> playAgain;
        
        // Normalisation de la saisie en majuscule
        playAgain = toupper(playAgain);
        
        // Vide le buffer d'entrée pour éviter les problèmes
        // avec les saisies ultérieures
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
    } while (playAgain == 'Y');  // Continue tant que l'utilisateur veut rejouer

    // =============================================
    // FIN DU PROGRAMME
    // =============================================
    return 0;  // Retourne 0 indiquant une exécution réussie
}