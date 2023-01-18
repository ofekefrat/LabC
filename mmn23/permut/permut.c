/*description*/

#include "permut.h"

int main(int argc, char *argv[]) {

    int i, c, count=0, found=0;
    char *word, *bank, *path;
    size_t len;
    FILE* input;
    path = argv[1];

    if (argc < REQ_ARG_COUNT) {
        printf("Not enough arguments! (2 required)\n");
        exit(0);
    }

    if (argc > REQ_ARG_COUNT) {
        printf("Excessive arguments! (2 required)\n");
        exit(0);
    }

    len = strlen(argv[2]);
    input = fopen(path, "r");

    if (input == NULL) {
        perror("_NULL_ could not open specified input file");
        exit(0);
    }

    if (feof(input)) {
        perror("_FEOF_ could not open specified input file");
        exit(0);
    }

    if (ferror(input)) {
        perror("_FERROR_ could not open specified input file");
        exit(0);
    }

    fseek(input, 0, SEEK_SET);
    word = (char*)calloc(len, sizeof(char));
    bank = (char*)calloc(len, sizeof(char));

    strcpy(bank, argv[2]);

    while ((c = fgetc(input)) != EOF) {
        for (i=0; i < len; i++) {
            if (c == bank[i]) {
                word[count++] = (char) c;
                bank[i] = EMPTY;
                break;
            }
        }

        if (i==len) { /* letter not in argument */
            memset(word, 0, len*sizeof(char));
            strcpy(bank, argv[2]);
            count=0;
        } /* very, very wasteful */

        if (count == len) { /* permutation found */
            if (!found) found=1;
            printf("%s\n", word);
            memset(word, 0, len*sizeof(char));
            strcpy(bank, argv[1]);
            count=0;
        }
    }

    fclose(input);
    if (!found) printf("No permutations found!\n");

    return 0;
}
