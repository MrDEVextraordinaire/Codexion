#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* task(void* arg) {
    char* name = ((char**)arg)[0];
    int delay = *((int*)((char**)arg)[1]);

    printf("%s starting\n", name);
    sleep(delay);
    printf("%s finished after %d seconds\n", name, delay);

    return NULL;
}

int main() {
    pthread_t t1, t2;

    char* name1 = "Thread-1";
    char* name2 = "Thread-2";
    int delay1 = 5;
    int delay2 = 1;

    // pack arguments for each thread
    void* args1[] = {name1, &delay1};
    void* args2[] = {name2, &delay2};

    pthread_create(&t1, NULL, task, args1);
    pthread_create(&t2, NULL, task, args2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Both threads are done\n");

    return 0;
}