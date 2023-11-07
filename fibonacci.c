#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint64_t fbmat_t[2][2];

uint64_t fibonacci(int n) {
    uint64_t curr = 1;
    uint64_t prev = 1;
    uint64_t pprev = 1;
    for (n = n - 2; n > 0; n--) {
        curr = prev + pprev;
        pprev = prev;
        prev = curr;
    }
    return curr;
}

void fb_mul(fbmat_t mat, fbmat_t fact) {
    uint64_t t00 = mat[0][0];
    uint64_t t01 = mat[0][1];
    uint64_t t10 = mat[1][0];
    uint64_t t11 = mat[1][1];
    mat[0][0] = t00 * fact[0][0] + t01 * fact[1][0];
    mat[0][1] = t00 * fact[0][1] + t01 * fact[1][1];
    mat[1][0] = t10 * fact[0][0] + t11 * fact[1][0];
    mat[1][1] = t10 * fact[0][1] + t11 * fact[1][1];
}

void fb_sqr(fbmat_t mat) {
    uint64_t t00 = mat[0][0];
    uint64_t t01 = mat[0][1];
    uint64_t t10 = mat[1][0];
    uint64_t t11 = mat[1][1];
    mat[0][0] = t00 * t00 + t01 * t10;
    mat[0][1] = t00 * t01 + t01 * t11;
    mat[1][0] = t10 * t00 + t11 * t10;
    mat[1][1] = t10 * t01 + t11 * t11;
}

uint64_t fibonacci_fast(int n) {
    fbmat_t base = {{1, 0}, {0, 1}};
    fbmat_t fact = {{1, 1}, {1, 0}};
    int cnt = n - 2;
    for (int i = 1; i <= cnt; i *= 2) {
        if (i > 1) {
            fb_sqr(fact);
        }
        if (i & cnt > 0) {
            fb_mul(base, fact);
        }
    }
    return base[0][0] + base[0][1];
}

int main(int argc, char* argv[]) {
    int n = 1;
    if (argc > 1) {
        n = atoi(argv[1]);
    }
    fbmat_t a = {{1,1},{1,1}};
    printf("fibonacci(%d): %llu\n", n,fibonacci(n));
    printf("fibonacci_fast(%d): %llu\n", n,fibonacci(n));
}