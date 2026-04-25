#include "./includes/codexion.h"
#include <unistd.h>

void *atomic_print(void *arg)
{
    t_coder *coder = (t_coder *)arg;
    pthread_mutex_t *print_lock;

    usleep(coder->id * 1000);
    print_lock = &coder->data->print_lock;
    pthread_mutex_lock(print_lock);
    printf("\ncoder N%d " ,coder->id);
    printf("printing at %lldms\n", (current_time() - coder->data->start_time));

    pthread_mutex_unlock(print_lock);
    return NULL;
}

int main(int argc, char **argv)
{
    int N = 8;
    t_coder coders[N];
    pthread_t threads[N];
    t_data data;

    data.start_time = current_time();
    pthread_mutex_init(&data.print_lock, NULL);

    for(int i = 0 ; i<N ; i++)
    {
        coders[i].id = i;
        coders[i].data = &data;
        pthread_create(&threads[i], NULL, atomic_print, &coders[i]);
    }

    for(int i = 0 ; i<N; i++)
        pthread_join(threads[i], NULL);

    if (!parsed_validated(argc, argv))
        return(1);
    return (0);
}
