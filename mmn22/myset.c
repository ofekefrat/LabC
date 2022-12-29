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

        if (strcmp(str, "stop") == 0) {
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

int getSetName() {
    int choice;
    char name[5];
    int r=scanf(" %s", name);
    if (r!=1 || strlen(name) < 4) {
        printf("Undefined set name\n");
        return -1;
    }
    choice = name[3] - 'A';
    if (name[0] != 'S' || name[1] != 'E' || name[2] != 'T' || choice < 0 || choice > 5) {
        printf("Undefined set name\n");
        return -1;
    }
    return choice;
}

void redefine(pSet setArr) {
    int choice, num, i, negative=0;
    choice = getSetName();
    if (choice == -1) return;

    set tempSet;
    emptySet(&tempSet);

    char buf[999];
    fgets(buf, 999, stdin);

    emptySet(&setArr[choice]);
    char* token = strtok(buf, ", ");

    while(token != NULL) {

        for (i=0; i < strlen(token); i++) {
            if (token[i] == '\n') {
                break;
            }
            if (!negative && token[0] == '-')
                negative = 1;
            else if (token[i] < '0' || token[i] > '9') {
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
        setArr[choice].sections[i].val = tempSet.sections[i].val;
    }
}

void print(pSet setArr) {
    int choice, counter=0, i, j;
    choice = getSetName();
    if (choice == -1) return;

    char buf[999];
    fgets(buf, 999, stdin);

    for (i=0; i < SECTIONS; i++) {
        if (setArr[choice].sections[i].val > 0) {
            for (j=0; j < SECTION_SIZE; j++) {
                if (counter != 0 && counter % LINE_PRINT_LENGTH == 0)
                    printf("\n");
                if (setArr[choice].sections[i].val & (unsigned long long) 1 << j) {
                    if (counter == 0) {
                        printf("SET%c = { ", ('A' + choice));
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
    int i, setInd1, setInd2, setInd3;
    if ((setInd1 = getSetName()) == -1) return;
    if ((setInd2 = getSetName()) == -1) return;
    if ((setInd3 = getSetName()) == -1) return;

    char buf[999];
    fgets(buf, 999, stdin);

    if (setInd1 != setInd3 && setInd2 != setInd3)
        emptySet(&setArr[setInd3]);

    for (i=0; i < SECTIONS; i++) {
        setArr[setInd3].sections[i].val = (setArr[setInd1].sections[i].val | setArr[setInd2].sections[i].val);
    }
}

void intersect(pSet setArr) {
    int i, setInd1, setInd2, setInd3;
    if ((setInd1 = getSetName()) == -1) return;
    if ((setInd2 = getSetName()) == -1) return;
    if ((setInd3 = getSetName()) == -1) return;

    char buf[999];
    fgets(buf, 999, stdin);

    if (setInd1 != setInd3 && setInd2 != setInd3)
        emptySet(&setArr[setInd3]);

    for (i=0; i < SECTIONS; i++) {
        setArr[setInd3].sections[i].val = setArr[setInd1].sections[i].val & setArr[setInd2].sections[i].val;
    }
}

void subset(pSet setArr) {
    int i, setInd1, setInd2, setInd3;
    if ((setInd1 = getSetName()) == -1) return;
    if ((setInd2 = getSetName()) == -1) return;
    if ((setInd3 = getSetName()) == -1) return;

    char buf[999];
    fgets(buf, 999, stdin);

    if (setInd1 != setInd3 && setInd2 != setInd3)
        emptySet(&setArr[setInd3]);

    for (i=0; i < SECTIONS; i++) {
        setArr[setInd3].sections[i].val = setArr[setInd1].sections[i].val & ~setArr[setInd2].sections[i].val;
    }
}

void symmetricDiff(pSet setArr) {
    int i, setInd1, setInd2, setInd3;
    if ((setInd1 = getSetName()) == -1) return;
    if ((setInd2 = getSetName()) == -1) return;
    if ((setInd3 = getSetName()) == -1) return;

    char buf[999];
    fgets(buf, 999, stdin);

    if (setInd1 != setInd3 && setInd2 != setInd3)
        emptySet(&setArr[setInd3]);

    for (i = 0; i < SECTIONS; i++) {
        setArr[setInd3].sections[i].val = (setArr[setInd1].sections[i].val ^ setArr[setInd2].sections[i].val);
    }
}