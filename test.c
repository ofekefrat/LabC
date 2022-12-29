//
// Created by ofeke on 30/11/2022.
//
#include "set.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    unsigned long long two = 1<<1;
    unsigned long long x = (two & (unsigned long long) 1<<33);
    if (x & (unsigned long long) 1<<33) {
        printf("1\n");
    }
    printf("%llu", x);
}