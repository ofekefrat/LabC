#include "set.h"

void emptySet(pSet target) {
    target->sections[0].val = 0;
    target->sections[1].val = 0;
}

void addMember(pSet target, int num) {
    target->sections[num/SECTION_SIZE].val |= (unsigned long long) 1 << (num % SECTION_SIZE);
}

void print_set(pSet targetSet, int* nums) {
    int counter=0, i, j;

    for (i=0; i < SECTIONS; i++) {
        if (targetSet->sections[i].val > 0) {
            for (j=0; j < SECTION_SIZE; j++) {
//                if (counter != 0 && counter % LINE_PRINT_LENGTH == 0)
//                    printf("\n");
                if (targetSet->sections[i].val & (unsigned long long) 1 << j) {
//                    if (counter == 0) {
//                        printf("\n{ ");
//                    }
//                    printf("%d ", j + i*SECTION_SIZE);
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

void read_set(pSet targetSet, pSet temp) {
    targetSet->sections[0].val = temp->sections[0].val;
    targetSet->sections[1].val = temp->sections[1].val;
}

void union_set(pSet s1, pSet s2, pSet targetSet) {
    targetSet->sections[0].val = (s1->sections[0].val | s2->sections[0].val);
    targetSet->sections[1].val = (s1->sections[1].val | s2->sections[1].val);
}

void intersect_set(pSet s1, pSet s2, pSet targetSet) {
    targetSet->sections[0].val = s1->sections[0].val & s2->sections[0].val;
    targetSet->sections[1].val = s1->sections[1].val & s2->sections[0].val;
}

void sub_set(pSet s1, pSet s2, pSet targetSet) {
    targetSet->sections[0].val = s1->sections[0].val & ~s2->sections[0].val;
    targetSet->sections[1].val = s1->sections[1].val & ~s2->sections[0].val;
}

void symdiff_set(pSet s1, pSet s2, pSet targetSet) {
    targetSet->sections[0].val = (s1->sections[0].val ^ s2->sections[0].val);
    targetSet->sections[1].val = (s1->sections[1].val ^ s2->sections[1].val);
}
