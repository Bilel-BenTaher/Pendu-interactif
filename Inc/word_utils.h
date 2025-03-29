#ifndef WORD_UTILS_H
#define WORD_UTILS_H

#include <string>

/**
 * @file word_utils.h
 * @brief Déclaration des fonctions utilitaires pour la gestion des mots
 * dans le jeu du pendu
 */

/**
 * @brief Charge un mot aléatoire depuis un fichier
 * @param path Chemin d'accès au fichier contenant les mots
 * @return Le mot sélectionné aléatoirement
 * @throws std::runtime_error Si le fichier n'est pas trouvé ou est vide
 * 
 * Le fichier doit contenir un mot par ligne. La fonction sélectionne
 * aléatoirement un mot parmi tous ceux disponibles dans le fichier.
 */
std::string LoadRandomWord(const std::string& path);

/**
 * @brief Compte le nombre de mauvaises lettres devinées
 * @param word Le mot à deviner
 * @param guessed Les lettres déjà proposées par le joueur
 * @return Le nombre de lettres incorrectes (entre 0 et la taille de 'guessed')
 * 
 * Compare chaque lettre devinée avec les lettres du mot secret
 * pour déterminer combien de mauvaises propositions ont été faites.
 */
int CountWrongGuesses(const std::string& word, const std::string& guessed);

/**
 * @brief Permet d'ajouter un mot personnalisé à la liste des mots
 * 
 * Demande à l'utilisateur de saisir un nouveau mot, le valide
 * (longueur, caractères autorisés) et l'ajoute au fichier de mots.
 * Affiche des messages d'erreur si la saisie est invalide.
 */
void AddCustomWord();

/**
 * @brief Affiche l'aide et les instructions du jeu
 * @return Le code de statut (0 pour succès)
 * 
 * Montre les règles du jeu, les commandes disponibles
 * et des conseils pour jouer. L'affichage est adapté
 * à la taille de la console.
 */
int DisplayHelp();

#endif // WORD_UTILS_H