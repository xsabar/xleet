#include <stdio.h>
#include <stdlib.h>

int gcd_minus(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    if (a == 1 || b == 1) return 1;
    if (a > b) {
        return gcd_minus(b, a - b);
    } else {
        return gcd_minus(a, b - a);
    }
}

int gcd_mod(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    if (a > b) {
        return gcd_mod(b, a % b);
    } else {
        return gcd_mod(a, b % a);
    }
}

int gcd_fast(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    if (a == 1 || b == 1) return 1;
    if ((a & 1) == 0 && (b & 1) == 0) {
        return gcd_mod(a / 2, b / 2) * 2;
    } else if ((a & 1) == 0) {
        return gcd_mod(a / 2, b);
    } else if ((b & 1) == 0) {
        return gcd_mod(a, b / 2);
    } else {
        if (a > b) {
            return gcd_mod(b, a - b);
        } else {
            return gcd_mod(a, b - a);
        }
    }
}

int main(int argc, char* argv[]) {
    int a = 0;
    int b = 0;
    if (argc < 3) {
        a = 120 * 1234;
        b = 120 * 1111;
    } else {
        a = atoi(argv[1]);
        b = atoi(argv[2]);
    }
    printf("gcd_minus(%d,%d): %d\n", a, b, gcd_minus(a, b));
    printf("gcd_mod(%d,%d)  : %d\n", a, b, gcd_mod(a, b));
    printf("gcd_fast(%d,%d) : %d\n", a, b, gcd_fast(a, b));
}