/*description*/

#include "permut.h"

int main(int argc, char *argv[]) {

    size_t len;
//    FILE* input;
    pQueue pq = createQueue();
    int c, count=0, found=0;

    if (argc < REQ_ARG_COUNT) {
        printf("Not enough arguments! (2 required)\n");
        exit(0);
    }

    if (argc > REQ_ARG_COUNT) {
        printf("Excessive arguments! (2 required)\n");
        exit(0);
    }

    len = strlen(argv[2]);
//    input = fopen(argv[1], "r");
//
//    if (input == NULL) {
//        perror("could not open specified input file");
//        exit(0);
//    }
//
//    if (feof(input)) {
//        printf("File is empty\n");
//        exit(0);
//    }
//
//    fseek(input, 0, SEEK_SET);

    while ((c = fgetc(stdin)) != '\n') { /* change \n */
        enQueue(pq, (char) c);
        count++;

        if (count >= len) {
            if (count != len) deQueue(pq);
            found += isWordValid(pq, argv[2]);
        }
    }

//    fclose(input);
    if (!found) printf("No permutations found!\n");

    return 0;
}

int isNodeInBank(pNode pn, char* bank) {
    int i;
    size_t size = strlen(bank);

    for (i=0; i < size; i++) {
        if (pn->key == bank[i]) {
            bank[i] = bank[size-1];
            bank[size-1] = '\0';
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

    currentNode = pq->front;
    tempBank = (char*) malloc(len*sizeof(char));
    if (tempBank == NULL) perror("tempBank failed to initialize\n");
    strcpy(tempBank, bank);

    for (i=0; i < strlen(bank); i++) {
        if (isNodeInBank(currentNode, tempBank)) currentNode = currentNode->next;
        else return 0;
    }

    printWord(pq);
    if (tempBank != NULL) free(tempBank);
    return 1;
}

void printWord(pQueue pq) {
    pNode currentNode;

    currentNode = pq->front;
    while (currentNode != NULL) {
        putchar(currentNode->key);
        currentNode = currentNode->next;
    }
    putchar('\n');
}