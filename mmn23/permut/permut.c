/*description*/

#include "permut.h"

int main(int argc, char *argv[]) {

    size_t len;
    FILE* input;
    pQueue pq = createQueue();
    int c, count=0, found=0;
    char* path;
    path = (char*)malloc(40);

    if (argc < REQ_ARG_COUNT) {
        printf("Not enough arguments! (2 required)\n");
        exit(0);
    }

    if (argc > REQ_ARG_COUNT) {
        printf("Excessive arguments! (2 required)\n");
        exit(0);
    }

    len = strlen(argv[2]);
    sprintf(path, "%s", ("~/CLionProjects/LabC/%s", argv[2])); /* remove */
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

    while ((c = fgetc(input)) != EOF) {
        enQueue(pq, (char) c);
        count++;

        if (count >= len) {
            if (count != len) deQueue(pq);
            found += isWordValid(pq, argv[2]);
        }
    }

    fclose(input);
    if (!found) printf("No permutations found!\n");

    return 0;
}

int isNodeInBank(pNode pn, char* bank) {
    int i;

    for (i=0; i < strlen(bank); i++) {
        if (pn->key == bank[i]) {
            bank[i] = EMPTY;
            return 1;
        }
    }
    return 0;
}

int isWordValid(pQueue pq, char* bank) {
    int i;
    pNode currentNode;
    size_t len = strlen(bank);
    char* tempBank;

    currentNode = pq->rear;
    tempBank = (char*) calloc(len, sizeof(char));
    if (tempBank == NULL) perror("tempBank failed to initialize\n");
    strcpy(tempBank, bank);

    for (i=0; i < strlen(bank); i++) {
        if (isNodeInBank(currentNode, tempBank)) currentNode = currentNode->next;
        else return 0;
    }

    printWord(pq,len);
    free(tempBank);
    return 1;
}

void printWord(pQueue pq, size_t len) {
    pNode currentNode;
    int i = (int) len-1;
    char* printable;
    printable = (char*) calloc(len, sizeof(char));
    if (printable == NULL) perror("printable failed to initialize\n");

    currentNode = pq->rear;

    while (currentNode != NULL && i >= 0) {
        printable[i--] = currentNode->key;
        currentNode = currentNode->next;
    }

    printf("%s\n", printable);
    free(printable);
}