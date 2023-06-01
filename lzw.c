#include "lzw.h"

dict* dict_new(){
    dict* new_dict = (dict*) malloc(sizeof(dict)*MAX_DICT_SIZE);
    for (int i=0; i<DICT_INIT_SIZE; i++){
        new_dict[i].word = (char*) malloc(sizeof(char)*2);
        new_dict[i].word[0] = (char)i;
        new_dict[i].word[1] = '\0';
        new_dict[i].code = i;
    }
    return new_dict;
}

void insert(dict *dict, char *word, int code) {
    dict[code].word = (char*) malloc(sizeof(char)*(strlen(word)+1));
    strcpy(dict[code].word, word);
    dict[code].code = code;
}

int find(dict *dict, int next_code, char *word) {
    for(int i=0; i<next_code; i++)
        if(!strcmp(dict[i].word, word))
            return dict[i].code;
    return -1;
}

void encode(FILE *input, FILE *output) {
    int next_code = DICT_INIT_SIZE;
    dict* dict = dict_new();
    char *last_valid = (char*) malloc(sizeof(char));
    last_valid[0] = '\0';
    char input_char[2];
    input_char[1] = '\0';

    fprintf(output, "%d ", CLEAR_CODE);

    while(!feof(input)){
        input_char[0] = fgetc(input);
        char* last_valid_input = (char*) malloc(sizeof(char)*(strlen(last_valid)+2));
        strcpy(last_valid_input, last_valid);
        strcat(last_valid_input, input_char);

        if(find(dict, next_code, last_valid_input) != -1){
            strcpy(last_valid, last_valid_input);
        } else {
            fprintf(output, "%d ", find(dict, next_code, last_valid));
            if(next_code < MAX_DICT_SIZE){
                insert(dict, last_valid_input, next_code);
                next_code++;
            }
            strcpy(last_valid, input_char);
        }
        free(last_valid_input);
    }
    fprintf(output, "%d ", find(dict, next_code, last_valid));
    fprintf(output, "%d ", END_CODE);
    free(last_valid);
    free(dict);
}

void decode(FILE *input, FILE *output) {
    int next_code = DICT_INIT_SIZE;
    dict* dict = dict_new();
    char* last_valid = (char*) malloc(sizeof(char));
    last_valid[0] = '\0';

    int input_code;
    fscanf(input, "%d", &input_code); // lire CLEAR_CODE

    while(!feof(input)){
        fscanf(input, "%d", &input_code);
        if(input_code == END_CODE)
            break;

        if(input_code < next_code){
            fprintf(output, "%s", dict[input_code].word);
            char* last_valid_input = (char*) malloc(sizeof(char)*(strlen(last_valid)+2));
            strcpy(last_valid_input, last_valid);
            strncat(last_valid_input, dict[input_code].word, 1);
            if(next_code < MAX_DICT_SIZE){
                insert(dict, last_valid_input, next_code);
                next_code++;
            }
            strcpy(last_valid, dict[input_code].word);
            free(last_valid_input);
        } else {
            char* last_valid_input = (char*) malloc(sizeof(char)*(strlen(last_valid)+3));
            strcpy(last_valid_input, last_valid);
            strncat(last_valid_input, last_valid, 1);
            fprintf(output, "%s", last_valid_input);
            if(next_code < MAX_DICT_SIZE){
                insert(dict, last_valid_input, next_code);
                next_code++;
            }
            strcpy(last_valid, last_valid_input);
            free(last_valid_input);
        }
    }
    free(last_valid);
    free(dict);
}
