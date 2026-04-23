#include "./includes/codexion.h"

int main(int argc, char **argv)
{

    if (!parsed_validated(argc, argv))
        return(1);
    
    printf("\nargc: %d\n",argc-1);
    printf("sucess\n");
}










// gettimeofday, usleep, write, malloc, free, printf, fprintf, strcmp, strlen, atoi, memset