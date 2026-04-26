#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
typedef struct {
    int counter;
} Shared;

Shared shared = {0};

void* increment(void* arg) {

    pthread_mutex_t *lock = (pthread_mutex_t *)arg;
    
    printf("Thread %lu started\n", (unsigned long)pthread_self());

    pthread_mutex_lock(lock);
    usleep(1000000);
    shared.counter++;
    pthread_mutex_unlock(lock);

    printf("Thread %lu finished\n", (unsigned long)pthread_self());
    return NULL;
}

int main() {
    pthread_t t1, t2, t3, t4, t5, t6;

    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, increment, &lock);
    pthread_create(&t2, NULL, increment, &lock);
    pthread_create(&t3, NULL, increment, &lock);
    pthread_create(&t4, NULL, increment, &lock);
    pthread_create(&t5, NULL, increment, &lock);
    pthread_create(&t6, NULL, increment, &lock);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);
    pthread_mutex_destroy(&lock);

    printf("Final counter = %d\n", shared.counter);

    return 0;
}