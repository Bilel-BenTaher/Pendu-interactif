#ifndef DRAWING_H
#define DRAWING_H

#include <string>

/**
 * @file drawing.h
 * @brief Déclaration des fonctions d'affichage pour le jeu du pendu
 */

/**
 * @brief Dessine le pendu selon le nombre d'essais incorrects
 * @param guessCount Nombre de mauvaises lettres devinées (0-6)
 * 
 * Affiche progressivement le dessin du pendu avec ses différentes parties
 * en fonction du nombre d'erreurs commises par le joueur.
 */
void DrawHangman(int guessCount = 0);

/**
 * @brief Affiche les lettres disponibles à deviner
 * @param guessed Lettres déjà proposées
 * @param word Mot à deviner
 * 
 * Montre quelles lettres n'ont pas encore été essayées,
 * en les comparant avec les lettres du mot à trouver.
 */
void PrintAvailableLetters(const std::string& guessed, const std::string& word);

/**
 * @brief Affiche le mot partiellement découvert et vérifie la victoire
 * @param word Mot complet à deviner
 * @param guessed Lettres déjà proposées
 * @return true si toutes les lettres du mot ont été trouvées, false sinon
 * 
 * Affiche le mot avec les lettres trouvées et des underscores pour les lettres manquantes.
 * Vérifie également si le joueur a gagné.
 */
bool PrintWordAndCheckWin(const std::string& word, const std::string& guessed);

/**
 * @brief Affiche un message formaté dans l'interface
 * @param message Texte à afficher
 * @param printTop Si true, ajoute une bordure supérieure
 * @param printBottom Si true, ajoute une bordure inférieure
 * @param isTitle Si true, applique un formatage spécial pour les titres
 * 
 * Permet d'afficher des messages avec un formatage cohérent dans l'interface du jeu,
 * avec des bordures optionnelles et un style différent pour les titres.
 */
void PrintMessage(const std::string& message, bool printTop, bool printBottom, bool isTitle);

/**
 * @brief Affiche une plage de lettres avec leur état
 * @param input Lettres déjà proposées
 * @param from Première lettre de la plage
 * @param to Dernière lettre de la plage
 * @param word Mot à deviner (pour vérifier l'utilité des lettres)
 * 
 * Affiche un groupe de lettres (ex: A-M) en indiquant lesquelles ont été utilisées
 * et lesquelles sont présentes dans le mot à trouver.
 */
void PrintLetters(const std::string& input, char from, char to, const std::string& word);

#endif // DRAWING_H