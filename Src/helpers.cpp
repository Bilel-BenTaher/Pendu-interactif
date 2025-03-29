#include "helpers.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>  // Pour les fonctions de console Windows
#endif

/**
 * @brief Change la couleur du texte dans la console (Windows seulement)
 * @param colorCode Code couleur Windows à appliquer (voir HangmanColors)
 * 
 * Cette fonction utilise l'API Windows pour modifier la couleur du texte.
 * Sous d'autres systèmes d'exploitation, cette fonction n'a aucun effet.
 */
void SetConsoleColor(int colorCode) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
#endif
}

/**
 * @brief Réinitialise la couleur de la console à la valeur par défaut
 * 
 * Sous Windows, utilise SetConsoleColor avec la couleur par défaut.
 * Sous Unix/Linux, émet le code ANSI de réinitialisation de couleur.
 */
void ResetConsoleColor() {
#ifdef _WIN32
    SetConsoleColor(HangmanColors::DEFAULT);
#else
    std::cout << HangmanColors::DEFAULT;
#endif
}

/**
 * @brief Affiche un message formaté dans un cadre stylisé
 * @param message Texte à afficher
 * @param printTop Si true, affiche une bordure supérieure
 * @param printBottom Si true, affiche une bordure inférieure
 * @param isTitle Si true, applique le style de titre
 * 
 * Le message est centré dans un cadre de 33 caractères de large.
 * Les titres sont affichés dans une couleur spécifique.
 * La fonction gère automatiquement la réinitialisation des couleurs.
 */
void PrintMessage(const std::string& message, bool printTop, bool printBottom, bool isTitle) {
    // Applique la couleur de titre si nécessaire
    if (isTitle) {
#ifdef _WIN32
        SetConsoleColor(HangmanColors::TITLE);
#else
        std::cout << HangmanColors::TITLE;
#endif
    }

    // Affiche la bordure supérieure si demandée
    if (printTop) {
        std::cout << "+---------------------------------+\n";
        std::cout << "|";
    } else {
        std::cout << "|";
    }

    // Centre le message en alternant les espaces avant/après
    bool front = true;
    std::string formatted = message;
    for (int i = message.length(); i < 33; i++) {
        formatted = front ? " " + formatted : formatted + " ";
        front = !front;
    }

    // Affiche le message formaté
    std::cout << formatted;

    // Affiche la bordure inférieure si demandée
    if (printBottom) {
        std::cout << "|\n";
        std::cout << "+---------------------------------+\n";
    } else {
        std::cout << "|\n";
    }

    // Réinitialise toujours la couleur après l'affichage
    ResetConsoleColor();
}