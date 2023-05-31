#include "lzw.h"

lzw_dict* dict_new(){
    lzw_dict* new_dict = (lzw_dict*) malloc(sizeof(lzw_dict)*MAX_DICT_SIZE);
    for (int i=0; i<DICT_INIT_SIZE; i++){
        new_dict[i].entry = (char*) malloc(sizeof(char)*2);
        new_dict[i].entry[0] = (char)i;
        new_dict[i].entry[1] = '\0';
        new_dict[i].code = i;
    }
    return new_dict;
}

void lzw_dict_insert(lzw_dict *dict, char *entry, int code) {
    dict[code].entry = (char*) malloc(sizeof(char)*(strlen(entry)+1));
    strcpy(dict[code].entry, entry);
    dict[code].code = code;
}

int lzw_dict_search(lzw_dict *dict, int next_code, char *entry) {
    for(int i=0; i<next_code; i++)
        if(!strcmp(dict[i].entry, entry))
            return dict[i].code;
    return -1;
}

void lzw_encode(FILE *input, FILE *output) {
    int next_code = DICT_INIT_SIZE;
    lzw_dict* dict = dict_new();
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

        if(lzw_dict_search(dict, next_code, last_valid_input) != -1){
            strcpy(last_valid, last_valid_input);
        } else {
            fprintf(output, "%d ", lzw_dict_search(dict, next_code, last_valid));
            if(next_code < MAX_DICT_SIZE){
                lzw_dict_insert(dict, last_valid_input, next_code);
                next_code++;
            }
            strcpy(last_valid, input_char);
        }
        free(last_valid_input);
    }
    fprintf(output, "%d ", lzw_dict_search(dict, next_code, last_valid));
    fprintf(output, "%d ", END_CODE);
    free(last_valid);
    free(dict);
}

void lzw_decode(FILE *input, FILE *output) {
    int next_code = DICT_INIT_SIZE;
    lzw_dict* dict = dict_new();
    char* last_valid = (char*) malloc(sizeof(char));
    last_valid[0] = '\0';

    int input_code;
    fscanf(input, "%d", &input_code); // lire CLEAR_CODE

    while(!feof(input)){
        fscanf(input, "%d", &input_code);
        if(input_code == END_CODE)
            break;

        if(input_code < next_code){
            fprintf(output, "%s", dict[input_code].entry);
            char* last_valid_input = (char*) malloc(sizeof(char)*(strlen(last_valid)+2));
            strcpy(last_valid_input, last_valid);
            strncat(last_valid_input, dict[input_code].entry, 1);
            if(next_code < MAX_DICT_SIZE){
                lzw_dict_insert(dict, last_valid_input, next_code);
                next_code++;
            }
            strcpy(last_valid, dict[input_code].entry);
            free(last_valid_input);
        } else {
            char* last_valid_input = (char*) malloc(sizeof(char)*(strlen(last_valid)+3));
            strcpy(last_valid_input, last_valid);
            strncat(last_valid_input, last_valid, 1);
            fprintf(output, "%s", last_valid_input);
            if(next_code < MAX_DICT_SIZE){
                lzw_dict_insert(dict, last_valid_input, next_code);
                next_code++;
            }
            strcpy(last_valid, last_valid_input);
            free(last_valid_input);
        }
    }
    free(last_valid);
    free(dict);
}
