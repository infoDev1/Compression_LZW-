#include "lzw.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <e|d> <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    input = fopen(argv[2], "rb");
    if (!input) {
        fprintf(stderr, "Error opening input file\n");
        return EXIT_FAILURE;
    }

    output = fopen(argv[3], "wb");
    if (!output) {
        fprintf(stderr, "Error opening output file\n");
        fclose(input);
        return EXIT_FAILURE;
    }

    switch (argv[1][0]) {
        case 'e':
            lzw_encode(input, output);
            break;
        case 'd':
            lzw_decode(input, output);
            break;
        default:
            fprintf(stderr, "Invalid operation\n");
            fclose(input);
            fclose(output);
            return EXIT_FAILURE;
    }

    fclose(input);
    fclose(output);

    return 0;
}
