#include "set.h"

int main() {

    char str[999]; /* no */
    int i, r=0;
    set sets[NUM_OF_SETS];

    for (i=0; i<NUM_OF_SETS; i++) {
        emptySet(&sets[i]);
    }

    while (r != EOF) {

        printf("\nPlease enter your command:\n");
        r = scanf("%s", str);

        if (str[strlen(str)-1] == ',') {
            printf("Illegal comma\n");
        }

        else if (strcmp(str, "stop") == 0) {
            printf("Stopping..");
            exit(0);
        }

        else if (strcmp(str, "read_set") == 0) {
            redefine(sets);
        }

        else if (strcmp(str, "print_set") == 0) {
            print(sets);
        }

        else if (strcmp(str, "union_set") == 0) {
            unionize(sets);
        }

        else if (strcmp(str, "intersect_set") == 0) {
            intersect(sets);
        }

        else if (strcmp(str, "sub_set") == 0) {
            subset(sets);
        }

        else if (strcmp(str, "symdiff_set") == 0) {
            symmetricDiff(sets);
        }

        else {
            printf("Undefined command name\n");
        }

        str[0] = '\0';
        fflush(stdin);
    }

    return 0;
}

int setCaller(char* str, int endOfCommand) {
    int choice;

    if (strlen(str) == 1 && str[0] == ',') {
        printf("Multiple consecutive commas\n");
        return -1;
    }

    if (strlen(str) < 4) {
        printf("Undefined set name\n");
        return -1;
    }

    if (endOfCommand) {
        if (strlen(str) > 4) {
            printf("Extraneous text after end of command\n");
            return -1;
        }
    }
    else {
        if (strlen(str) > 5) {
            printf("Undefined set name\n");
            return -1;
        }
    }

    choice = str[3] - 'A';
    if (str[0] != 'S' || str[1] != 'E' || str[2] != 'T' || choice < 0 || choice > 5) {
        printf("Undefined set name\n");
        return -1;
    }

    if (!endOfCommand && strlen(str) < 5) {
        printf("Missing comma\n");
        return -1;
    }

    return choice;
}

void redefine(pSet setArr) {
    int targetInd, num, i, negative=0;
    char targetSet[6];
    scanf(" %s", targetSet);
    targetInd = setCaller(targetSet, 1);
    if (targetInd == -1) return;

    set tempSet;
    emptySet(&tempSet);

    char buf[999];
    fgets(buf, 999, stdin);

    emptySet(&setArr[targetInd]);
    char* token = strtok(buf, ", ");

    while(token != NULL) {

        for (i=0; i < strlen(token); i++) {
            if (token[i] == '\n') {
                break;
            }
            if (!negative && token[0] == '-')
                negative = 1;
            else if (token[i] < '0' || token[i] > '9' || token[i] == '\0') {
                printf("Invalid set member - not an integer\n");
                return;
            }
        }

        num = strtol(token, NULL, DECIMAL_BASE);
        if (num == -1) break;

        if (negative || num > MAX_NUM) {
            printf("Invalid set member - value out of range\n");
            return;
        }
        addMember(&tempSet, num);

        token = strtok(NULL, ", ");
    }

    if (token == NULL) {
        printf("List of set members not terminated correctly\n");
        return;
    }

    for (i=0; i < SECTIONS; i++) {
        setArr[targetInd].sections[i].val = tempSet.sections[i].val;
    }
}

void print(pSet setArr) {
    int targetInd, counter=0, i, j;
    char targetSet[5];
    scanf(" %s", targetSet);
    targetInd = setCaller(targetSet,1);
    if (targetInd == -1) return;

    for (i=0; i < SECTIONS; i++) {
        if (setArr[targetInd].sections[i].val > 0) {
            for (j=0; j < SECTION_SIZE; j++) {
                if (counter != 0 && counter % LINE_PRINT_LENGTH == 0)
                    printf("\n");
                if (setArr[targetInd].sections[i].val & (unsigned long long) 1 << j) {
                    if (counter == 0) {
                        printf("SET%c = { ", ('A' + targetInd));
                    }
                    printf("%d ", j + i*SECTION_SIZE);
                    counter++;
                }
            }
        }
    }

    if (counter == 0)
        printf("The set is empty\n");
    else
        printf("}\n");
}

void unionize(pSet setArr) {
    int i, set1Ind, set2Ind, targetInd;
    char set1[6], set2[6], target[5];
//    char line[20];
//    fgets(line, 20, stdin);
    if ((set1Ind = setCaller(set1,0)) == -1) return;
    if ((set2Ind = setCaller(set2,0)) == -1) return;
    if ((targetInd = setCaller(target,1)) == -1) return;

    if (set1Ind != targetInd && set2Ind != targetInd)
        emptySet(&setArr[targetInd]);

    for (i=0; i < SECTIONS; i++) {
        setArr[targetInd].sections[i].val = (setArr[set1Ind].sections[i].val | setArr[set2Ind].sections[i].val);
    }
}

void intersect(pSet setArr) {
    char set1[6], set2[6], target[5];
    int i, set1Ind, set2Ind, targetInd;
    scanf(" %s %s %s", set1, set2, target);
    if ((set1Ind = setCaller(set1,0)) == -1) return;
    if ((set2Ind = setCaller(set2,0)) == -1) return;
    if ((targetInd = setCaller(target,1)) == -1) return;

    if (set1Ind != targetInd && set2Ind != targetInd)
        emptySet(&setArr[targetInd]);

    for (i=0; i < SECTIONS; i++) {
        setArr[targetInd].sections[i].val = setArr[set1Ind].sections[i].val & setArr[set2Ind].sections[i].val;
    }
}

void subset(pSet setArr) {
    int i, set1Ind, set2Ind, targetInd;
    char set1[6], set2[6], target[5];
    scanf(" %s %s %s", set1, set2, target);
    if ((set1Ind = setCaller(set1,0)) == -1) return;
    if ((set2Ind = setCaller(set2,0)) == -1) return;
    if ((targetInd = setCaller(target,1)) == -1) return;

    if (set1Ind != targetInd && set2Ind != targetInd)
        emptySet(&setArr[targetInd]);

    for (i=0; i < SECTIONS; i++) {
        setArr[targetInd].sections[i].val = setArr[set1Ind].sections[i].val & ~setArr[set2Ind].sections[i].val;
    }
}

void symmetricDiff(pSet setArr) {
    int i, set1Ind, set2Ind, targetInd;
    char set1[6], set2[6], target[5];
    scanf(" %s %s %s", set1, set2, target);
    if ((set1Ind = setCaller(set1,0)) == -1) return;
    if ((set2Ind = setCaller(set2,0)) == -1) return;
    if ((targetInd = setCaller(target,1)) == -1) return;

    if (set1Ind != targetInd && set2Ind != targetInd)
        emptySet(&setArr[targetInd]);

    for (i = 0; i < SECTIONS; i++) {
        setArr[targetInd].sections[i].val = (setArr[set1Ind].sections[i].val ^ setArr[set2Ind].sections[i].val);
    }
}