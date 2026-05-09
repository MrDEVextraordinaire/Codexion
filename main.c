#include "./includes/codexion.h"
#include <unistd.h>

void *atomic_print(void *arg)
{
    t_coder *coder = (t_coder *)arg;
    pthread_mutex_t *print_lock;

    // usleep(coder->id * 1000);

    print_lock = &coder->data->print_lock;
    pthread_mutex_lock(print_lock);
    printf("\ncoder N%d " ,coder->id);
    printf("printing at %lldms\n", (current_time() - coder->data->start_time));
    printf("\ncoder N%d " ,coder->id);
    printf("printing at %lldms\n", (current_time() - coder->data->start_time));    printf("\ncoder N%d " ,coder->id);
    printf("printing at %lldms\n", (current_time() - coder->data->start_time));    printf("\ncoder N%d " ,coder->id);
    printf("printing at %lldms\n", (current_time() - coder->data->start_time));    printf("\ncoder N%d " ,coder->id);
    printf("printing at %lldms\n", (current_time() - coder->data->start_time));    printf("\ncoder N%d " ,coder->id);
    printf("printing at %lldms\n", (current_time() - coder->data->start_time));
    printf("\n1-eat");
    printf("2-sleep");
    printf("3-pray");
    


    // pthread_mutex_unlock(print_lock);
    return NULL;
}

int main(int argc, char **argv)
{
    // t_dongle dongle;
    t_data data;
    t_config config;

    if (!parsed_validated(argc, argv))
        return(1);
    
    config.number_of_coders = atoi(argv[1]);
    t_coder *coders = malloc(sizeof(t_coder)*config.number_of_coders);
    pthread_t *threads = malloc(sizeof(pthread_t) * config.number_of_coders);
    // t_dongle *dongles = malloc(sizeof(t_dongle) * config.number_of_coders);

    data.start_time = current_time();
    pthread_mutex_init(&data.print_lock, NULL);

    for(int i = 0 ; i < config.number_of_coders ; i++)
    {
        coders[i].id = i;
        coders[i].data = &data;
        pthread_create(&threads[i], NULL, atomic_print, &coders[i]);
    }
    for(int i = 0 ;i < config.number_of_coders; i++)
        pthread_join(threads[i], NULL);
    
    free(coders);
    free(threads);
    return (0);
}
