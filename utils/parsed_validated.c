#include "../includes/codexion.h"

static int validate_refactor_time(char *argv)
{
    if (atoi(argv) < 1)
{
		fprintf(stderr, "[Error] time to refactor has to be more than 0\n");
		return (0);
}
    return (1);
}

static int validate_scheduler(char *argv)
{
    if ((strcmp(argv, "fifo") == 0))
    {
        printf("argv[8]: %s",argv );
        printf("\n8th argument  fifo \n");
    }
    else if (((strcmp(argv, "edf")) == 0))
    {
        printf("argv[8]: %s",argv );
        printf("\n8th argument  edf \n");
    }
    else
    {
        fprintf(stderr, "[Error] 8th arg has to be fifo or edf, exiting\n");
        return (0);
    }
    return (1);
}

static int all_ints(char **argv)
{
    int i = 1;
    int j = 0;

    while (i < 8 && argv[i])
    {
        j = 0;
        while(argv[i][j])
        {
            if (!is_digit(argv[i][j]))
            {
                fprintf(stderr, "\n[Error] args have to be integers, exiting\n");
                return(0);
            }
            j++;
        }
        i++;
    }
    if (atoi(argv[1]) < 1)
    {
        fprintf(stderr, "\n[Error] you must have at least one coder\n");
        return(0);
    }

    return (1);
}

static int argc_valid(int argc)
{
    if (argc != 9)
    {
        fprintf(stderr, "[Error] Plese input 8 valid arguments\n");
        return (0);
    }
    return (1);
}

int parsed_validated(int argc, char **argv)
{
    if (!argc_valid(argc))
        return (0);
    if(!all_ints(argv))
        return 0;
    if (!validate_refactor_time(argv[5]))
        return (0);
    if (!validate_scheduler(argv[8]))
        return (0);
    return (1);
}

