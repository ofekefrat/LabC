/*description*/

#include "permut.h"

int main(int argc, char *argv[]) {

    int i, c, count=0, found=0;
    char *word, *bank;
    size_t len;
    FILE* input;

    if (argc < 3) {
        printf("Not enough arguments! (2 required)\n");
        exit(0);
    }

    if (argc > 3) {
        printf("Excessive arguments! (2 required)\n");
        exit(0);
    }

    len = strlen(argv[2]);
    input = fopen(argv[1], "r");

    if (!input) {
        perror("could not open specified input file");
        exit(0);
    }

    word = calloc(len, sizeof(char));
    bank = calloc(len, sizeof(char));

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
            while (c != ' ' && c != '\n') {
                if (c == EOF) exit(0); /* temp */
                c = fgetc(input);
            }
        }

        if (count == len) { /* permutation found */
            if (!found) found=1;
            printf("%s\n", word);
            memset(word, 0, len*sizeof(char));
            strcpy(bank, argv[1]);
            count=0;
        }
    }

    if (!found) printf("No permutations found!\n");

    return 0;
}
