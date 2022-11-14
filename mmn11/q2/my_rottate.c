
#include "my_rottate.h"

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
        return (a<<b | a >> (SIZE+1-b));
    }
    return (a>>b | a << (SIZE+1-b));
}

void display(unsigned int num) {

    int i=0;
    double t;

    printf("Decimal: %u\n"
           "Octal: %o\n"
           "Hexadecimal: %x\n"
           "Binary:", num, num, num);
    while (i <= SIZE) { /* printing base-2 (binary) representation */
        if (!(i % CHAR_BIT))
            printf(" "); /* separate the bytes with a space, according to the size of a single byte */
        t = pow(2, SIZE - i); /* checking the bit values from left to right (using the index) */
        printf("%d", (num >= t));
        if (num >= t)
            num -= (int)t;
        i++;
    }
    printf("\n");
}