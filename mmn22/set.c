#include "set.h"

void emptySet(pSet target) {
    target->sections[0].val = 0;
    target->sections[1].val = 0;
}

void addMember(pSet target, int num) {
    target->sections[num/SECTION_SIZE].val |= (unsigned long long) 1 << (num % SECTION_SIZE);
}