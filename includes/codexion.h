#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_s {
    int number_of_coders;
    int time_to_burnout;
    int time_to_compile;
    int time_to_debug;
    int time_to_refactor;
    int number_of_compiles_required;
    int dongle_cooldown;
    char *scheduler;
    struct data_s *next;
}   data_struct;

int is_digit(char c);
int parsed_validated(int argc, char **argv);
