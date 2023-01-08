#include "set.h"

/* emptySet: truncate the entire contents of the set pointed to by the pointer argument.*/
void emptySet(pSet target) {
    int i;
    for (i=0; i < SECTIONS; i++)
        target->sections[i].value = 0;
}

/* addMember: Add the number in the argument as a member to the set pointed to by the pointer.*/
void addMember(pSet target, int num) {
    target->sections[num/SECTION_SIZE].value |= (unsigned long) 1 << (num % SECTION_SIZE);
}

/* print_set: method to read all members from the set pointed to by the argument. The method then saves
 * all existing values in the integer array pointed to by the second argument, for the actuallyPrint method to.. well..
 * ACTUALLY print the values. If the set is empty, the method instead returns a single value (-1) to the array,
 * letting actuallyPrint know that the set was empty.*/
void print_set(pSet targetSet, int* nums) {
    int counter=0, i, j;

    for (i=0; i < SECTIONS; i++)
        if (targetSet->sections[i].value > 0)
            for (j=0; j < SECTION_SIZE; j++)
                if (targetSet->sections[i].value & (unsigned long) 1 << j)
                    nums[counter++] = j + i*SECTION_SIZE;

    if (counter == 0)
        nums[0] = -1;
}

/* read_set: method to redefine the set pointed to by the first argument, with the members of the temporary set
 * passed by getSetMembers in the second argument.*/
void read_set(pSet targetSet, pSet temp) {

    int i;
    for (i=0; i < SECTIONS; i++)
        targetSet->sections[i].value = temp->sections[i].value;
}

/* union_set: method to perform the union operation on the two sets pointed to by the first two arguments,
 * and laying the result on the set in the third argument.*/
void union_set(pSet s1, pSet s2, pSet targetSet) {
    int i;
    for (i=0; i < SECTIONS; i++)
        targetSet->sections[i].value = (s1->sections[i].value | s2->sections[i].value);
}

/* intersect_set: method to perform intersection on the two sets pointed to by the first two arguments,
 * and laying the result on the set in the third argument.*/
void intersect_set(pSet s1, pSet s2, pSet targetSet) {
    int i;
    for (i=0; i < SECTIONS; i++)
        targetSet->sections[i].value = s1->sections[i].value & s2->sections[i].value;
}

/* sub_set: method to subtract the members from the set in the second argument, from the set in the first argument,
 * and laying the result on the set in the third argument.*/
void sub_set(pSet s1, pSet s2, pSet targetSet) {
    int i;
    for (i=0; i < SECTIONS; i++)
        targetSet->sections[i].value = s1->sections[i].value & ~s2->sections[i].value;
}

/* symdiff_set: method to perform the symmetric difference operation on the two sets pointed to by
 * the first two arguments, and laying the result on the set in the third argument.*/
void symdiff_set(pSet s1, pSet s2, pSet targetSet) {
    int i;
    for (i=0; i < SECTIONS; i++)
        targetSet->sections[i].value = (s1->sections[i].value ^ s2->sections[i].value);
}
