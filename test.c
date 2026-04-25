#include <stdio.h>
#include <pthread.h>

typedef struct {
    int counter;
} Shared;

Shared shared = {0};

void* increment(void* arg) {

    pthread_mutex_t *lock = (pthread_mutex_t *)arg;

    int localc = 0;
    for (int i = 0; i < 10000000; i++) {
        localc++;
    }
    printf("Thread %lu started\n", (unsigned long)pthread_self());

    pthread_mutex_lock(lock);
    shared.counter += localc;
    pthread_mutex_unlock(lock);

    printf("Thread %lu finished\n", (unsigned long)pthread_self());
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, increment, &lock);
    pthread_create(&t2, NULL, increment, &lock);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&lock);

    printf("Final counter = %d\n", shared.counter);

    return 0;
}