#ifndef LZW_H
#define LZW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DICT_SIZE 4096
#define DICT_INIT_SIZE 258
#define END_CODE 257
#define CLEAR_CODE 256

/**
 * @brief Structure représentant une case d'un dictionnaire
 * 
 */
typedef struct _dict {
    char * word;
    int code;
    struct _dict *next;
} dict;

/**
 * @brief Insère une nouvelle entrée dans le dictionnaire.
 * 
 * @param dict Le dictionnaire dont lequel on effectue l'insertion
 * @param word La chaîne de caractère à insérer 
 * @param code Le code la chaîne
 */
void insert(dict *dict, char *word, int code);

/**
 * @brief Cherche une entrée dans le dictionnaire et renvoie son code.
 * 
 * @param dict Le dictionnaire dont lequel on effectue la recherche
 * @param next_code prochain code
 * @param word Le mot à rechercher
 * @return int Le code du mot s'il est présent dans le dictionnaire, -1 sinon
 */
int find(dict *dict, int next_code, char *word);

/**
 * @brief Encode un fichier d'entrée en utilisant l'algorithme LZW et écrit le résultat dans un fichier de sortie.
 * 
 * @param input Le fichier d'input (lecture)
 * @param output Le fichier d'output (ecriture)
 */
void encode(FILE *input, FILE *output);

/**
 * @brief Décode un fichier d'entrée encodé avec l'algorithme LZW et écrit le résultat dans un fichier de sortie.
 * 
 * @param input Le fichier d'input (lecture)
 * @param output Le fichier d'output (ecriture)
 */
void decode(FILE *input, FILE *output);

#endif 