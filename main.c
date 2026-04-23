#include "codexion.h"

int main(int argc, char **argv)
{
    int i = 1;
    while (argv[i])
    {
        int parsed = atoi(argv[i]);
        printf("\nargs: %d\n", parsed);
        i++;
    }


    printf("\nargc: %d\n",argc-1);
}










// gettimeofday, usleep, write, malloc, free, printf, fprintf, strcmp, strlen, atoi, memset