#include "./includes/codexion.h"
#include <unistd.h>

long ms_timer()
{
    struct timeval startime;
    long startime_in_ms;

    gettimeofday(&startime, NULL);
    startime_in_ms = startime.tv_sec * 1000 + startime.tv_usec / 1000;
    return (startime_in_ms);
}

int main(int argc, char **argv)
{
    t_data data;

    if (!parsed_validated(argc, argv))
        return(1);
    data.start_time = ms_timer();


    printf("\nargc: %d\n",argc-1);
    printf("sucess\n");

    printf("data.start_time: %lli\n", data.start_time );
    return (0);
}







// gettimeofday, usleep, write, malloc, free, printf, fprintf, strcmp, strlen, atoi, memset