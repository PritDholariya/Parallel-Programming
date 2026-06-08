#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    long long int n = atoll(argv[1]);
    double temp = 0.0;

    for (long long int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            temp += 1.0 / (2 * i + 1);
        } else {
            temp -= 1.0 / (2 * i + 1);
        }
    }

    double pi = temp * 4;
    printf("Approximation of pi is : %.10f\n", pi);

    return 0;
}