#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
typedef struct {
    int counter;
} Shared;

Shared shared = {0};

int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }

    return 1;
}



void* increment(void* arg) {
    pthread_mutex_t *lock = (pthread_mutex_t *)arg;
    
    
    pthread_mutex_lock(lock);
    // usleep(100000);
    for (int i = 0; i < 2000000000000000; i++) {
        shared.counter += is_prime(i);
        if(is_prime(i)){
            printf("Thread %lu reached: %u\n", (unsigned long)pthread_self(),i);
        // usleep(10000);

        }
    }
    pthread_mutex_unlock(lock);

    // printf("Thread %lu finished\n", (unsigned long)pthread_self());
    return NULL;
}

int main() {
    pthread_t t[6];

    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);
    for(int i = 0; i < 6; i++)
        pthread_create(&t[i], NULL, increment, &lock);
    for(int i = 0; i < 6; i++)
        pthread_join(t[i], NULL);
    pthread_mutex_destroy(&lock);

    printf("Final counter = %d\n", shared.counter);

    return 0;
}