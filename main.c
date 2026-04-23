#include "./includes/codexion.h"

int main(int argc, char **argv)
{
    int j = 0;
    int i = 1;
    int parsed;

    while (argv[i])
    {
        if (i < 8)
        {
            j = 0;
            while(argv[i][j])
            {
                if (argv[i][j] && !is_digit(argv[i][j]))
                {
                    fprintf(stderr, "\n[Error] args have to be integers, exiting\n");
                    return(1);
                }
                j++;
            }
            parsed = atoi(argv[i]);
            printf("\nargs: %d\n", parsed);
        }
        else if (i == 8)
        {
            if ((strcmp(argv[i], "fifo") == 0))
            {
                printf("argv[8]: %s",argv[i] );
                printf("\n8th argument  fifo \n");
            }
            else if (((strcmp(argv[i], "edf")) == 0))
            {
                printf("argv[8]: %s",argv[i] );
                printf("\n8th argument  edf \n");
            }
            else
            {
                fprintf(stderr, "[Error] 8th arg has to be fifo or edf, exiting\n");
                return (2);
            }
            
        }
        i++;
    }
    printf("\nargc: %d\n",argc-1);

    printf("sucess\n");
}










// gettimeofday, usleep, write, malloc, free, printf, fprintf, strcmp, strlen, atoi, memset