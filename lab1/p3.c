#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    long long int start;
    long long int jump;
    long long int n;
    double temp;
} ThreadData;

void* compute_pi(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    double sum = 0.0;

    for (long long int i = data->start; i < data->n; i += data->jump) {
        if (i % 2 == 0) {
            sum += 1.0 / (2 * i + 1);
        } else {
            sum -= 1.0 / (2 * i + 1);
        }
    }

    data->temp = sum;
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {

    long long int n = atoll(argv[1]);
    int num_threads = atoi(argv[2]);

    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    for (int i = 0; i < num_threads; i++) {
        thread_data[i].start = i;
        thread_data[i].jump = num_threads;
        thread_data[i].n = n;

        pthread_create(&threads[i], NULL, compute_pi, &thread_data[i]);
    }

    double total_sum = 0.0;

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].temp;
    }

    double pi = total_sum * 4;
    printf("Approximation of pi: %.15f\n", pi);

    return 0;
}