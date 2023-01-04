#include "set.h"

int main() {

    int c, i, target, ind[COMMON_ARG_AMOUNT];
    char word[COMMAND_MAX_LENGTH], line[INPUT_LINE_MAX_LENGTH];
    set temp, sets[NUM_OF_SETS];
    pSet s1, s2, targetSet;
    FILE *input = fopen("input.txt", "w+");


    for (i=0; i<NUM_OF_SETS; i++) {
        emptySet(&sets[i]);
    }

    printf("Please enter your command:\n");
    while (fgets(line, INPUT_LINE_MAX_LENGTH, stdin)) {

        memset(word, 0, sizeof(word));
        i=0;
        s1=NULL;
        s2=NULL;
        targetSet=NULL;
        fflush(stdin);
        freopen("input.exe", "w+", input);

        fprintf(input, "%s", line);
        rewind(input);

        printf("\nYou've entered: %s",line);

        while ((c = fgetc(input)) != '\n' && c != EOF && i < COMMAND_MAX_LENGTH) {
            if (c == ' ' || c == '\t') {
                if (word[0] != 0) break;
            }
            else {
                word[i++] = (char) c;
            }
        }

        if (i == 0) {
            printf("ERROR: Nothing entered\n");
        }

        else if (word[i-1] == ',') {
            printf("ERROR: Illegal comma\n");
        }

        else if (strlen(word) > 13) {
            printf("ERROR: Unknown command name\n");
        }

        else if (strcmp(word, "stop") == 0) {
            printf("Stopping..");
            fclose(input);
            exit(0);
        }

        else if (strcmp(word, "read_set") == 0) {
            if ((target = getSetName(0, input)) == ERROR) continue;
            targetSet = &sets[target];

            getSetMembers(&temp, input);
            read_set(targetSet, &temp);

            emptySet(&temp);
        }

        else if (strcmp(word, "print_set") == 0) {
            if ((target = getSetName(1, input)) == ERROR) continue;
            targetSet = &sets[target];

            actuallyPrint(targetSet);
        }

        else if (strcmp(word, "union_set") == 0 || strcmp(word, "intersect_set") == 0
                || strcmp(word, "sub_set") == 0 || strcmp(word, "symdiff_set") == 0) {

            readLine(ind, input);
            if (ind[0] == ERROR) continue;

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
            printf("ERROR: Undefined command name\n");

        printf("\nPlease enter your command:\n");
    }
    printf("\nERROR: EOF received\n");
    fclose(input);

    return 0;
}

void getSetMembers(pSet temp, FILE* input) {
    char digits[NUM_MAX_LENGTH];
    int i, ch, num;
    emptySet(temp);

    while(1) {

        memset(digits, 0, sizeof(digits));
        i=0;

        while ((ch = fgetc(input)) != ',' && ch != '\n' && i < NUM_MAX_LENGTH) {
            if (ch == ' ' || ch == '\t') {
                if (!(digits[0] == '-' && digits[1] == '1') && i != 0) { /* not -1 */
                    printf("ERROR: Missing comma\n");
                    return;
                }
            }
            else if ((ch < '0' || ch > '9') && ch != '-') {
                printf("ERROR: Invalid set member - not an integer\n");
                return;
            }
            else {
                digits[i++] = (char) ch;
            }
        }
        if (i == 0 && ch == ',') {
            printf("ERROR: Multiple consecutive commas\n");
            return;
        }
        num = strtol(digits, NULL, DECIMAL_BASE);

        if (num == ERROR) break;
        if (ch == '\n') {
            printf("ERROR: List of set members not terminated correctly\n");
            return;
        }
        if (num < 0 || num > MAX_NUM) {
            printf("ERROR: Invalid set member - value out of range\n");
            return;
        }
        addMember(temp, num);
    }
}

int getSetName(int final, FILE* input) {
    int index, ch, i=0, last=0;
    char setName[SET_NAME_MAX_LENGTH];

    memset(setName, 0, sizeof(setName));

    while ((ch = fgetc(input)) != ',' && ch != '\n' && i < SET_NAME_MAX_LENGTH) {
        if (ch == ' ' || ch == '\t') {
            if (!final && i != 0) {
                printf("ERROR: Missing comma\n");
                return ERROR;
            }
        }
        else {
            setName[i++] = (char) ch;
        }
    }

    if (ch == '\n') last=1;

    if (i == 0) {
        if (ch == ',')
            printf("ERROR: Multiple consecutive commas\n");
        else
            printf("ERROR: No operators entered\n");

        return ERROR;
    }

    if (strlen(setName) != 4) {
        printf("ERROR: Undefined set name\n");
        return ERROR;
    }

    index = setName[3] - 'A';
    if (setName[0] != 'S' || setName[1] != 'E' || setName[2] != 'T' || index < 0 || index > 5) {
        printf("ERROR: Undefined set name\n");
        return ERROR;
    }

    if (final && !last) {
        printf("ERROR: Extraneous text after end of command\n");
        return ERROR;
    }

    if (last && !final) {
        printf("ERROR: Missing parameter\n");
        return ERROR;
    }

    return index;
}

void readLine(int* indexes, FILE* input) {
    int counter=0;
    int final=0;

    while (!final) {
        if (counter == COMMON_ARG_AMOUNT-1) final=1;
        indexes[counter] = getSetName(final, input);

        if (indexes[counter] == ERROR) {
            indexes[0] = ERROR;
            break;
        }
        counter++;
    }
}

void actuallyPrint(pSet targetSet) {
    int i, nums[MAX_NUM];
    memset(nums, 0, sizeof(nums));

    print_set(targetSet, nums);
    if (nums[0] == ERROR) {
        printf("The set is empty\n");
        return;
    }

    printf("\n{ %d ", nums[0]);
    for (i = 1; i < MAX_NUM && nums[i] != 0; i++) {
        if (i != 0 && i % LINE_PRINT_LENGTH == 0)
            printf("\n");

        printf("%d ", nums[i]);
    }
    printf("}\n");
}