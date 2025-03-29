#include "drawing.h"
#include "helpers.h"
#include <vector>
#include <algorithm>
#include <cctype>

/**
 * @brief Dessine le pendu selon le nombre d'essais incorrects
 * @param guessCount Nombre de mauvaises lettres devinées (0-6)
 * 
 * Affiche progressivement le dessin du pendu avec ses différentes parties
 * en fonction du nombre d'erreurs. Le dessin devient plus complet à chaque erreur.
 * La couleur change en rouge lorsque des erreurs sont commises.
 */
void DrawHangman(int guessCount) {
    PrintMessage("", false, false, false);  // Ligne vide pour l'espacement
    
    // Dessin ASCII du pendu avec différents états selon guessCount
    std::vector<std::string> hangmanDrawing = {
        " +---+   ",  // Base toujours visible
        guessCount >= 1 ? " |   |   " : "     |   ",  // Poteau vertical
        guessCount >= 3 ? " O   |   " : (guessCount >= 1 ? "     |   " : "         "),  // Tête
        guessCount >= 6 ? "/|\\  |   " :  // Corps complet
            (guessCount >= 5 ? "/|   |   " :  // Bras droit
            (guessCount >= 4 ? "/     |   " : "      |   ")),  // Bras gauche
        guessCount >= 7 ? " |   |   " : "     |   ",  // Tronc
        guessCount >= 9 ? "/ \\  |___" :  // Jambes complètes
            (guessCount >= 8 ? "/     |___" : "      |___")  // Jambe gauche
    };

    // Applique la couleur rouge si des erreurs ont été commises
#ifdef _WIN32
    SetConsoleColor(guessCount > 0 ? HangmanColors::WRONG : HangmanColors::DEFAULT);
#else
    std::cout << (guessCount > 0 ? HangmanColors::WRONG : HangmanColors::DEFAULT);
#endif

    // Affiche chaque ligne du dessin
    for (const auto& line : hangmanDrawing) {
        PrintMessage(line, false, false, false);
    }
    
    ResetConsoleColor();  // Réinitialise la couleur
}

/**
 * @brief Affiche une plage de lettres avec leur état
 * @param input Lettres déjà proposées
 * @param from Première lettre de la plage
 * @param to Dernière lettre de la plage
 * @param word Mot à deviner (pour vérifier l'utilité des lettres)
 * 
 * Affiche les lettres de 'from' à 'to' en coloriant différemment :
 * - Vert si la lettre est dans le mot
 * - Rouge si la lettre n'est pas dans le mot
 * - Non coloriée si la lettre n'a pas encore été proposée
 */
void PrintLetters(const std::string& input, char from, char to, const std::string& word) {
    std::string s;
    for (char i = from; i <= to; i++) {
        char upperChar = toupper(i);
        if (input.find(upperChar) == std::string::npos) {
            // Lettre non encore proposée
            s += i;
            s += " ";
        } else {
            // Lettre déjà proposée
            bool isInWord = (word.find(upperChar) != std::string::npos);
#ifdef _WIN32
            SetConsoleColor(isInWord ? HangmanColors::CORRECT : HangmanColors::WRONG);
#else
            std::cout << (isInWord ? HangmanColors::CORRECT : HangmanColors::WRONG);
#endif
            s += i;
            s += " ";
            ResetConsoleColor();
        }
    }
    PrintMessage(s, false, false, false);
}

/**
 * @brief Affiche les lettres disponibles regroupées en deux lignes
 * @param guessed Lettres déjà proposées
 * @param word Mot à deviner
 * 
 * Affiche d'abord les lettres de A à M, puis de N à Z sur une nouvelle ligne
 * avec un titre "AVAILABLE LETTERS" en haut et une bordure.
 */
void PrintAvailableLetters(const std::string& guessed, const std::string& word) {
    PrintMessage("AVAILABLE LETTERS", true, true, true);  // Titre avec bordures
    PrintLetters(guessed, 'A', 'M', word);  // Première moitié de l'alphabet
    PrintLetters(guessed, 'N', 'Z', word);  // Deuxième moitié de l'alphabet
}

/**
 * @brief Affiche le mot partiellement découvert et vérifie la victoire
 * @param word Mot complet à deviner
 * @param guessed Lettres déjà proposées
 * @return true si toutes les lettres ont été trouvées, false sinon
 * 
 * Affiche le mot avec :
 * - Les lettres trouvées en vert
 * - Les lettres manquantes comme "_ "
 * Vérifie également si toutes les lettres ont été découvertes.
 */
bool PrintWordAndCheckWin(const std::string& word, const std::string& guessed) {
    bool won = true;
    std::string s;
    
    // Construit la représentation du mot avec les lettres trouvées
    for (char c : word) {
        char upperC = toupper(c);
        if (guessed.find(upperC) == std::string::npos) {
            won = false;
            s += "_ ";  // Lettre non trouvée
        } else {
            // Lettre trouvée - affichée en vert
#ifdef _WIN32
            SetConsoleColor(HangmanColors::CORRECT);
#else
            std::cout << HangmanColors::CORRECT;
#endif
            s += c;
            s += " ";
            ResetConsoleColor();
        }
    }
    PrintMessage(s, false, true, false);  // Affiche le mot avec bordure basse
    return won;
}