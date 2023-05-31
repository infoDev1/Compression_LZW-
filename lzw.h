#ifndef LZW_H
#define LZW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DICT_SIZE 4096
#define DICT_INIT_SIZE 258
#define END_CODE 257
#define CLEAR_CODE 256

// Structure pour une entrée dans le dictionnaire LZW.
typedef struct lzw_dict {
    char *entry;
    int code;
    struct lzw_dict *next;
} lzw_dict;

/**
 * Insère une nouvelle entrée dans le dictionnaire.
 */
void lzw_dict_insert(lzw_dict *dict, char *entry, int code);

/**
 * Cherche une entrée dans le dictionnaire et renvoie son code.
 */
int lzw_dict_search(lzw_dict *dict, int next_code, char *entry);

/**
 * Encode un fichier d'entrée en utilisant l'algorithme LZW et écrit le résultat dans un fichier de sortie.
 */
void lzw_encode(FILE *input, FILE *output);

/**
 * Décode un fichier d'entrée encodé avec l'algorithme LZW et écrit le résultat dans un fichier de sortie.
 */
void lzw_decode(FILE *input, FILE *output);

#endif // LZW_H
