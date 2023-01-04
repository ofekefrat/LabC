#include "set.h"

void emptySet(pSet target) {
    int i;
    for (i=0; i < SECTIONS; i++)
        target->sections[i].value = 0;
}

void addMember(pSet target, int num) {
    target->sections[num/SECTION_SIZE].value |= (unsigned long) 1 << (num % SECTION_SIZE);
}

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

void read_set(pSet targetSet, pSet temp) {
    int i;
    for (i=0; i < SECTIONS; i++)
        targetSet->sections[0].value = temp->sections[0].value;
}

void union_set(pSet s1, pSet s2, pSet targetSet) {
    int i;
    for (i=0; i < SECTIONS; i++)
        targetSet->sections[i].value = (s1->sections[i].value | s2->sections[i].value);
}

void intersect_set(pSet s1, pSet s2, pSet targetSet) {
    int i;
    for (i=0; i < SECTIONS; i++)
        targetSet->sections[i].value = s1->sections[i].value & s2->sections[i].value;
}

void sub_set(pSet s1, pSet s2, pSet targetSet) {
    int i;
    for (i=0; i < SECTIONS; i++)
        targetSet->sections[i].value = s1->sections[i].value & ~s2->sections[i].value;
}

void symdiff_set(pSet s1, pSet s2, pSet targetSet) {
    int i;
    for (i=0; i < SECTIONS; i++)
        targetSet->sections[i].value = (s1->sections[i].value ^ s2->sections[i].value);
}
