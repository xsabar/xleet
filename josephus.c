#include <stdio.h>
#include <stdlib.h>

void print_array(int a[], size_t n) {
    for (int i = 0; i < n - 1; i++) {
        printf("%d,", a[i]);
    }
    printf("%d\n", a[n - 1]);
}

void josephus_queue(size_t n, size_t m, int a[]) {
    int b[n];
    for (int i = 0; i < n; i++) {
        b[i] = i + 1;
    }
    int top = 0;
    int tail = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            b[tail++] = b[top++];
            top = top % n;
            tail = tail % n;
        }
        a[i] = b[top++];
        top = top % n;
    }
    
}

void josephus_math(size_t n, size_t m, int a[]) {
    for (int i = 0; i < n; i++) {
        a[i] = (m - 1) % (n - i);
        for (int j = n - i + 1; j <= n; j++) {
            a[i] = ((m - 1) % j + a[i] + 1) % j;
        }
        ++a[i];
    }
}

int josephus_kth(size_t n, size_t m, int k) {
    int x = (m - 1) % (n - k + 1);
    for (int i = n - k + 2; i <= n; i++) {
        x = ((m - 1) % i + x + 1) % i;
    }
    return x + 1;
}

int main(int argc, char* argv[]) {
    int n = 0;
    int m = 0;
    int k = 0;
    if (argc >= 3) {
        n = atoi(argv[1]);
        m = atoi(argv[2]);
        if (argc > 3) {
            k = atoi(argv[3]);
        }
    } else {
        n = 11;
        m = 3;
    }
    int a[n];
    josephus_queue(n, m, a);
    print_array(a, n);
    josephus_math(n, m, a);
    print_array(a, n);
    if (k != 0) {
        if (k < 0) {
            k = n + k + 1;
        }
        printf("josephus queue:%d\n", a[k - 1]);
        printf("josephus math :%d\n", josephus_kth(n, m, k));
    }
    return 0;
}