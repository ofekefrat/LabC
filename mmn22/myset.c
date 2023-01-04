#include "set.h"

int main() {

    int c=0, count, i, target, members[MAX_NUM], ind[COMMON_ARG_AMOUNT];
    char word[COMMAND_MAX_LENGTH];
    set temp, sets[NUM_OF_SETS];
    pSet s1, s2, targetSet;


    for (i=0; i<NUM_OF_SETS; i++) {
        emptySet(&sets[i]);
    }

    while (c != EOF) {

        memset(word, 0, sizeof(word));
        memset(members, 0, sizeof(members));
        count=0;
        s1=NULL;
        s2=NULL;
        targetSet=NULL;

        printf("\nPlease enter your command:\n");
        while ((c = getchar()) != '\n' && c != EOF && count < COMMAND_MAX_LENGTH) {
            if (c == ' ' || c == '\t') {
                if (word[0] != '\0') break;
            }
            else {
                word[count++] = (char) c;
            }
        }

        if (count == 0) {
            printf("Nothing entered\n");
        }

        else if (word[count-1] == ',') {
            printf("Illegal comma\n");
        }

        else if (strlen(word) > 13) {
            printf("Unknown command name\n");
        }

        else if (strcmp(word, "stop") == 0) {
            printf("Stopping..");
            exit(0);
        }

        else if (strcmp(word, "read_set") == 0) {
            if ((target = getSetName(0)) == -1) break;
            targetSet = &sets[target];

            getSetMembers(&temp);
            read_set(targetSet, &temp);

            emptySet(&temp);
        }

        else if (strcmp(word, "print_set") == 0) {
            if ((target = getSetName(1)) == -1) break;
            targetSet = &sets[target];

            print_set(targetSet, members);

        }

        else if (strcmp(word, "union_set") == 0 || strcmp(word, "intersect_set") == 0
                || strcmp(word, "sub_set") == 0 || strcmp(word, "symdiff_set") == 0) {

            readLine(ind);
            if (ind[0] == -1) break;

            s1 = &sets[ind[0]];
            s2 = &sets[ind[1]];
            targetSet = &sets[ind[2]];

            if (ind[0] != ind[2] && ind[1] != ind[2])
                emptySet(targetSet);

            if (strcmp(word, "union_set") == 0) union_set(s1, s2, targetSet);
            else if (strcmp(word, "intersect_set") == 0) intersect_set(s1, s2, targetSet);
            else if (strcmp(word, "sub_set") == 0) sub_set(s1, s2, targetSet);
            else if (strcmp(word, "symdiff_set") == 0) symdiff_set(s1, s2, targetSet);
        }
        else
            printf("Undefined command name\n");

        fflush(stdin);
    }

    printf("\nERROR: EOF received\n");

    return 0;
}

void getSetMembers(pSet temp) {
    char digits[NUM_MAX_LENGTH];
    int i, ch, num;
    emptySet(temp);

    while(1) {

        memset(digits, 0, sizeof(digits));
        i=0;

        while ((ch = getchar()) != ',' && ch != '\n' && i < NUM_MAX_LENGTH) {
            if (ch == ' ' || ch == '\t') {
                if (!(digits[0] == '-' && digits[1] == '1') && digits[0] != '\0') { /* not -1 */
                    printf("Missing comma\n");
                    return;
                }
            }
            else if ((ch < '0' || ch > '9') && ch != '-') {
                printf("Invalid set member - not an integer\n");
                return;
            }
            else {
                digits[i++] = (char) ch;
            }
        }
        num = strtol(digits, NULL, DECIMAL_BASE);

        if (num == -1) break;
        if (ch == '\n') {
            printf("List of set members not terminated correctly\n");
            return;
        }
        if (num < 0 || num > MAX_NUM) {
            printf("Invalid set member - value out of range\n");
            return;
        }
        addMember(temp, num);
    }
}

int getSetName(int final) {
    int index, ch, i=0, last=0;
    char setName[SET_NAME_MAX_LENGTH];

    memset(setName, 0, sizeof(setName));

    while ((ch = getchar()) != ',' && ch != '\n' && i < SET_NAME_MAX_LENGTH) {
        if (ch == ' ' || ch == '\t') {
            if (!final && setName[0] != '\0') {
                printf("Missing comma\n");
                return -1;
            }
        }
        else {
            setName[i++] = (char) ch;
        }
    }

    if (ch == '\n') last=1;

    if (i == 0) {
        printf("No operators entered\n");
        return -1;
    }

    if (setName[0] == ',') {
        printf("Multiple consecutive commas\n");
        return -1;
    }

    if (strlen(setName) != 4) {
        printf("Undefined set name\n");
        return -1;
    }

    index = setName[3] - 'A';
    if (setName[0] != 'S' || setName[1] != 'E' || setName[2] != 'T' || index < 0 || index > 5) {
        printf("Undefined set name\n");
        return -1;
    }

    if (final && !last) {
        printf("Extraneous text after end of command\n");
        return -1;
    }

    if (last && !final) {
        printf("Missing parameter\n");
        return -1;
    }

    return index;
}

void readLine(int* indexes) {
    int counter=0;
    int final=0;

    while (!final) {
        if (counter == COMMON_ARG_AMOUNT-1) final=1;
        indexes[counter] = getSetName(final);

        if (indexes[counter] == -1) {
            indexes[0] = -1;
            break;
        }
        counter++;
    }
}