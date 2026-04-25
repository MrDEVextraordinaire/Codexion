#include "../includes/codexion.h"

int is_digit(char c)
{
    if (c >= 48 && c <= 57)
        return 1;
    return 0;
}

long long current_time()
{
    struct timeval startime;
    long startime_in_ms;
    gettimeofday(&startime, NULL);
    startime_in_ms = startime.tv_sec * 1000 + startime.tv_usec / 1000;
    return (startime_in_ms);
}
