/* A "set calculator" capable of defining 6 different sets. Each set can
 * contain integers in the range [0,127] inclusive. The calculator can then print a set's values, and perform
 * basic set operations between any two sets: intersection, union, subtraction, and symmetric difference.
 * The calculator then copies the result onto another set (or onto one of the operators, decided by the user).
 */
#include "set.h"

int main() {

    /* c: buffer reader for fgetc();
     * target: temporary index holder for simplicity;
     * ind[]: same as target, only for when multiple indexes are required.*/
    int c, i, target, ind[COMMON_ARG_AMOUNT];

    /* command[]: array to hold the command name for processing;
     * line[]: array to hold the entire line for printing and
     * later sending to the input file.*/
    char command[COMMAND_MAX_LENGTH], line[INPUT_LINE_MAX_LENGTH];

    /* temp: set instance for read_set to use as a middle-man, until testing is complete.
     * sets[]: the array of sets to hold the information required for calculations.*/
    set temp, sets[NUM_OF_SETS];

    /* s1, s2, targetSet: pointers to hold the reference to the required sets, passed by the methods.*/
    pSet s1, s2, targetSet;

    /* input: file buffer, mainly implemented for the purpose of printing the line back to the user and still being
     * able to read it with getc, letter by letter.*/
    FILE *input;
    if ((input = fopen("input.txt", "w+")) == NULL) {
        printf("Error opening input processing file\n");
        exit(1);
    }

    for (i=0; i<NUM_OF_SETS; i++) {
        emptySet(&sets[i]);
    }

    printf("Please enter your command:\n");
    while (fgets(line, INPUT_LINE_MAX_LENGTH, stdin)) {

        /* reset everything command-related */
        memset(command, 0, sizeof(command));
        i=0;
        target=0;
        s1=NULL;
        s2=NULL;
        targetSet=NULL;
        freopen("input.exe", "w+", input);
        if (input == NULL) {
            printf("Error opening input processing file\n");
            exit(1);
        }

        fprintf(input, "%s", line); /* pass the line to the processing file */
        rewind(input); /*bring the cursor back to the beginning to read the contents.*/

        printf("\nYou've entered: %s",line);

        while ((c = fgetc(input)) != '\n' && c != EOF && i < COMMAND_MAX_LENGTH) { /* reading and approving command*/
            if (c == ' ' || c == '\t') { /* allow any amount of spaces and tabs between words */
                if (i != 0) break;
            }
            else {
                command[i++] = (char) c;
            }
        }

        if (i == 0) { /* no valuable input has been entered (all white spaces) */
            printf("ERROR: Nothing entered\n");
        }

        else if (command[i - 1] == ',' || command[0] == ',') {
            printf("ERROR: Illegal comma\n");
        }

        else if (strlen(command) > COMMAND_MAX_LENGTH-2) {
            printf("ERROR: Unknown command name\n");
        }

        else if (strcmp(command, "stop") == 0) {
            printf("Stopping..\n");
            fclose(input);
            exit(0);
        }

        else if (strcmp(command, "read_set") == 0) {
            if ((target = getSetName(0, input)) != ERROR) {
                targetSet = &sets[target];
                getSetMembers(targetSet, &temp, input);
                emptySet(&temp);
                printf("New SET%c:", 'A' + target);
                actuallyPrint(targetSet);
            }
        }

        else if (strcmp(command, "print_set") == 0) {
            if ((target = getSetName(1, input)) != ERROR) {
                targetSet = &sets[target];
                actuallyPrint(targetSet);
            }
        }

        else if (strcmp(command, "union_set") == 0 || strcmp(command, "intersect_set") == 0
                 || strcmp(command, "sub_set") == 0 || strcmp(command, "symdiff_set") == 0) {

            readLine(ind, input);
            if (ind[0] != ERROR) {
                s1 = &sets[ind[0]];
                s2 = &sets[ind[1]];
                targetSet = &sets[ind[2]];

                if (ind[0] != ind[2] && ind[1] != ind[2])
                    emptySet(targetSet);

                if (strcmp(command, "union_set") == 0) union_set(s1, s2, targetSet);
                else if (strcmp(command, "intersect_set") == 0) intersect_set(s1, s2, targetSet);
                else if (strcmp(command, "sub_set") == 0) sub_set(s1, s2, targetSet);
                else if (strcmp(command, "symdiff_set") == 0) symdiff_set(s1, s2, targetSet);
                printf("New SET%c:\n", 'A' + target);
                actuallyPrint(targetSet);
            }
        }

        else {
            printf("ERROR: Undefined command name\n");
        }

        printf("\nPlease enter your command:\n");
    }

    printf("\nERROR: EOF received\n");
    fclose(input);

    return 0;
}

/* getSetMembers: method to help read_set receive all integers from the rest of the input buffer passed by the argument,
 * and making sure they're all in range and all numbers, and that the line was correctly terminated by -1.
 * The method defines a temporary set to be copied from by read_set, and then sends it
 * on its way if everything is in order. If any problems are found, prints a detailed error message
 * and terminates the current operation, waiting for a new command.*/
void getSetMembers(pSet targetSet, pSet temp, FILE* input) {
    /* digits[]: an array to process each letter before turning it into a number*/
    char digits[NUM_MAX_LENGTH];

    /* ch: buffer reader for fgetc()
     * num: variable to store the new group member or the terminator -1*/
    int i, ch, num, endOfNumFlag;
    emptySet(temp);

    while(1) {

        /* reset what's necessary */
        memset(digits, 0, sizeof(digits));
        i=0;
        endOfNumFlag=0;

        while ((ch = fgetc(input)) != ',' && ch != '\n' && i < NUM_MAX_LENGTH) {
            if (ch == ' ' || ch == '\t') {
                if (!(digits[0] == '-' && digits[1] == '1') && i != 0 && !endOfNumFlag) { /* not -1 */
                    endOfNumFlag=1;
                }
            }
            else if ((ch < '0' || ch > '9') && !(ch == '-' && i == 0)) {
                printf("ERROR: Invalid set member - not an integer\n");
                return;
            }
            else {
                if (endOfNumFlag) {
                    printf("ERROR: Missing comma\n");
                    return;
                }
                digits[i++] = (char) ch;
            }
        }

        if (i == 0 && ch == ',') {
            printf("ERROR: Multiple consecutive commas\n");
            return;
        }
        num = strtol(digits, NULL, DECIMAL_BASE);

        if (num == -1) break;
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
    read_set(targetSet, temp);
}

/* getSetName: reads a word from the input buffer passed in the argument, expecting it to be a defined set name
 * and returning its index in the set array if everything is correct.
 * The first argument should be 0 if the word is not the final operator, meaning a comma is to be expected at the end,
 * and 1 if the word is the final word to be expected. If any problems are found, prints a detailed error message
 * and terminates the current operation, waiting for a new command.*/
int getSetName(int final, FILE* input) {
    /*last: indicator whether the loop was terminated by \n, making this the last set*/
    int index, ch, i=0, last=0, endOfWordFlag=0;
    char setName[SET_NAME_MAX_LENGTH]; /* setName[]: array to hold the input for processing */

    memset(setName, 0, sizeof(setName));

    while ((ch = fgetc(input)) != ',' && ch != '\n' && i < SET_NAME_MAX_LENGTH) {
        if (ch == ' ' || ch == '\t') {
            if (!final && i != 0 && !endOfWordFlag) {
                endOfWordFlag=1;
            }
        }
        else {
            if (endOfWordFlag) {
                printf("ERROR: Missing comma\n");
                return ERROR;
            }
            setName[i++] = (char) ch;
        }
    }

    if (ch == '\n') last=1;

    if (i == 0) {
        if (ch == ',') {
            printf("ERROR: Multiple consecutive commas\n");
        }
        else {
            printf("ERROR: No operators entered\n");
        }

        return ERROR;
    }

    if (strlen(setName) != SET_NAME_MAX_LENGTH-1) {
        printf("ERROR: Undefined set name\n");
        return ERROR;
    }

    index = setName[3] - 'A';
    if (setName[0] != 'S' || setName[1] != 'E' || setName[2] != 'T' || index < 0 || index > NUM_OF_SETS-1) {
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

/* readLine: method to correctly read 3 set names from the input buffer passed by the argument,
 * for use in all basic set operation methods (union_set, intersect_set, sub_set and symdiff_set)
 * the method saves the indexes in the array pointed to by the pointer argument, to be used.
 * If any problems are found, prints a detailed error message and terminates the current operation,
 * waiting for a new command.*/
void readLine(int* indexes, FILE* input) {
    int counter=0; /* counter: keeps count of how many sets were successfully named */
    int final=0; /* final: flag to indicate if we're expecting the last set*/

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

/* actuallyPrint: method to print out all members of the set pointed to by the argument,
 * beginning and ending with curly brackets, and spaces in between.
 * If the set is empty, prints a message accordingly instead.*/
void actuallyPrint(pSet targetSet) {
    int i, nums[MAX_NUM]; /* nums[]: an array to hold all the members received from print_set */
    memset(nums, 0, sizeof(nums));

    print_set(targetSet, nums);
    if (nums[0] == -1) {
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