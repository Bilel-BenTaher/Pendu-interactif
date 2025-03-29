#ifndef HELPERS_H
#define HELPERS_H

#include <string>

/**
 * @file helpers.h
 * @brief Déclaration des fonctions utilitaires et des constantes de couleur
 * pour le jeu du pendu (multi-plateforme)
 */

/**
 * @namespace HangmanColors
 * @brief Définit les codes couleurs pour Windows 
 * 
 * Fournit des constantes pour les couleurs utilisées dans le jeu,
 * avec des implémentations différentes selon le système d'exploitation.
 */
namespace HangmanColors {
#ifdef _WIN32
    // Codes couleur pour Windows (API Console)
    const int DEFAULT = 7;     ///< Couleur par défaut (gris clair)
    const int TITLE = 11;      ///< Couleur pour les titres (cyan clair)
    const int CORRECT = 10;    ///< Couleur pour les bonnes réponses (vert clair)
    const int WRONG = 12;      ///< Couleur pour les erreurs (rouge clair)
    const int HIGHLIGHT = 14;  ///< Couleur pour les éléments importants (jaune)
#else
    // Codes ANSI pour les terminaux Unix/Linux/macOS
    const std::string DEFAULT = "\033[0m";     ///< Réinitialisation de couleur
    const std::string TITLE = "\033[1;33m";    ///< Titres en jaune gras
    const std::string CORRECT = "\033[1;32m";  ///< Bonnes réponses en vert gras
    const std::string WRONG = "\033[1;31m";    ///< Erreurs en rouge gras
    const std::string HIGHLIGHT = "\033[1;36m";///< Surbrillance en cyan gras
#endif
}

/**
 * @brief Change la couleur du texte dans la console (Windows seulement)
 * @param colorCode Code couleur Windows à appliquer
 * 
 * Cette fonction n'a d'effet que sous Windows. 
 * les couleurs sont gérées via les codes ANSI directement dans les strings.
 */
void SetConsoleColor(int colorCode);

/**
 * @brief Réinitialise la couleur de la console à la valeur par défaut
 * 
 * Sous Windows, restaure la couleur originale.
 */
void ResetConsoleColor();

/**
 * @brief Affiche un message formaté dans la console
 * @param message Texte à afficher
 * @param printTop Si true, ajoute une ligne de séparation au-dessus
 * @param printBottom Si true, ajoute une ligne de séparation en-dessous
 * @param isTitle Si true, applique le style de titre (couleur différente)
 * 
 * Cette fonction gère automatiquement les couleurs selon la plateforme
 * et permet d'afficher des messages avec un formatage cohérent.
 */
void PrintMessage(const std::string& message, bool printTop = true, bool printBottom = true, bool isTitle = false);

#endif // HELPERS_H