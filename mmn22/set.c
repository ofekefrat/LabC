#include "set.h"

void emptySet(pSet target) {
    int i;
    for (i=0; i < SECTIONS; i++)
        target->sections[i].val = 0;
}

void addMember(pSet target, int num) {
    target->sections[num/SECTION_SIZE].val |= (unsigned long) 1 << (num % SECTION_SIZE);
}

void print_set(pSet targetSet, int* nums) {
    int counter=0, i, j;

    for (i=0; i < SECTIONS; i++)
        if (targetSet->sections[i].val > 0)
            for (j=0; j < SECTION_SIZE; j++)
                if (targetSet->sections[i].val & (unsigned long) 1 << j)
                    nums[counter++] = j + i*SECTION_SIZE;

    if (counter == 0)
        nums[0] = -1;
}

void read_set(pSet targetSet, pSet temp) {
    int i;
    for (i=0; i < SECTIONS; i++)
        targetSet->sections[0].val = temp->sections[0].val;
}

void union_set(pSet s1, pSet s2, pSet targetSet) {
    int i;
    for (i=0; i < SECTIONS; i++)
        targetSet->sections[i].val = (s1->sections[i].val | s2->sections[i].val);
}

void intersect_set(pSet s1, pSet s2, pSet targetSet) {
    int i;
    for (i=0; i < SECTIONS; i++)
        targetSet->sections[i].val = s1->sections[i].val & s2->sections[i].val;
}

void sub_set(pSet s1, pSet s2, pSet targetSet) {
    int i;
    for (i=0; i < SECTIONS; i++)
        targetSet->sections[i].val = s1->sections[i].val & ~s2->sections[i].val;
}

void symdiff_set(pSet s1, pSet s2, pSet targetSet) {
    int i;
    for (i=0; i < SECTIONS; i++)
        targetSet->sections[i].val = (s1->sections[i].val ^ s2->sections[i].val);
}
