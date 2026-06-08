#include <stdio.h>

int main() {
    long long int values[] = {10, 100, 1000, 10000, 100000};
    int count = 5;

    for (int v = 0; v < count; v++) {
        long long int n = values[v];
        double temp = 0.0;

        for (long long int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                temp += 1.0 / (2 * i + 1);
            } else {
                temp -= 1.0 / (2 * i + 1);
            }
        }

        double pi = temp * 4;

        printf("n = %lld ----- Approximation of pi is  %.15f\n", n, pi);
    }

    return 0;
}