
#include "my_rottate.h"

unsigned int my_rottate(unsigned int a, int b) {

    while (b != 0) {
        if (b>0) {
            unsigned int temp = a%2;
            a = a>>1;
            if (temp)
                a += (unsigned int)pow(2, SIZE);
            b--;
        }

        if (b<0) {
            int temp = (a >= (unsigned int)pow(2, SIZE));
            a = a<<1;
            if (temp)
                a++;
            b++;
        }
    }

    return a;
}

int main() {

    unsigned int num;
    int distance;
    int i=0;
    double t;

    printf("Please enter a non-negative number: \n");
    if ((scanf("%u", &num)) == 1) {
        printf("Please enter distance: \n");
        if ((scanf("%d", &distance)) == 1) {
            printf("Before rotation: %u\n", num);
            num = my_rottate(num, distance);
            printf("After rotation: \n"
                   "Decimal: %u\n"
                   "Octal: %o\n"
                   "Hexadecimal: %x\n"
                   "Binary:", num, num, num);
            while (num>=0 && i <= SIZE) {
                if (!(i%8))
                    printf(" ");
                t = pow(2, SIZE - i);
                printf("%d", (num >= t));
                if (num >= t)
                    num -= (int)t;
                i++;
            }
            printf("\n");
        }
    }

    return 0;
}