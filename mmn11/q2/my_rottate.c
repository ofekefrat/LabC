
#include "my_rottate.h"

int int_len();
unsigned int my_rottate(unsigned int, int);
void display(unsigned int);

int main() {

    unsigned int num;
    int distance;

    printf("Please enter a non-negative number: \n");
    scanf("%u", &num);
    printf("Please enter distance: \n");
    scanf("%d", &distance);
    printf("Before rotation:\n");
    display(num); /* printing the values before the rotation */
    num = my_rottate(num, distance);
    printf("\nAfter rotation: \n"); /* printing the values after the rotation */
    display(num);

    return 0;
}

unsigned int my_rottate(unsigned int a, int b) {

    if (b<0) {
        b = -b; /* changing the distance value to its absolute value, to make the shifts correctly */
        return (a<<b | a >> (int_len()-b));
    }
    return (a>>b | a << (int_len()-b));
}

void display(unsigned int num) {

    int i=0;

    printf("Decimal: %u\n"
           "Octal: %o\n"
           "Hexadecimal: %x\n"
           "Binary:", num, num, num);
    while (i <= int_len()-1) { /* printing base-2 (binary) representation */
        if (!(i % CHAR_BIT))
            printf(" "); /* separate the bytes with a space, according to the size of a single byte */
        if (num & (1 << (int_len()-1-i)))
            printf("1");
        else
            printf("0");
        i++;
    }
    printf("\n");
}

int int_len() { /* getting int size according to machine */

    unsigned int x = ~0; /* max unsigned int value (all 1's) */
    int i;

    for (i = 0; x != 0; i++) {
        x = x >> 1;
    }
    return i;
}