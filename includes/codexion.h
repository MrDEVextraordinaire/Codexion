/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itemlali <itemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 18:56:14 by itemlali          #+#    #+#             */
/*   Updated: 2026/05/14 03:03:45 by itemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <limits.h>
#include <unistd.h>

#define NUMBER_OF_CODERS_ARG		1
#define TIME_TO_BURNOUT_ARG			2
#define TIME_TO_COMPILE_ARG			3
#define TIME_TO_DEBUG_ARG			4
#define TIME_TO_REFACTOR_ARG		5
#define N_REQUIRED_COMPILES_ARG		6
#define DONGLE_COOLDOWN_ARG			7
#define SCHEDULER_ARG				8
#define EXPECTED_ARGS				9

#define TRUE						1
#define FALSE						0

typedef struct s_dongle			t_dongle;
typedef struct s_data			t_data;
typedef struct s_coder_queue	t_coder_queue;
typedef struct s_config			t_config;
typedef struct s_coder			t_coder;

typedef struct s_data
{
	t_config			*config;
	t_coder				*coders;
	t_dongle			*dongles;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		death_lock;
	pthread_t			*threads;
	pthread_t			monitor;
	long long			start_time;
	int					simulation_over;
}						t_data;

typedef struct s_coder
{
	int					id;
	long long			last_compiled;
	int					compile_count;
	t_dongle			*left_dongle;
	t_dongle			*right_dongle;
	t_data				*data;
}						t_coder;


typedef struct s_dongle
{
	pthread_mutex_t		dongle_lock;
	pthread_cond_t		cond;
	long long			last_released;
	int					in_use;
	t_coder_queue		*min_heap;
	int					heap_size;
}						t_dongle;

typedef struct s_coder_queue
{
	int					coder_id;
	long long			deadline;
	long long			request_time;
}						t_coder_queue;

typedef struct s_config
{
	int					number_of_coders;
	long long			time_to_burnout;
	long long			time_to_compile;
	long long			time_to_debug;
	long long			time_to_refactor;
	int					number_of_compiles_required;
	long long			dongle_cooldown;
	char				*scheduler;
}						t_config;

int						ft_isdigit(char c);
int						parsed_validated(int argc, char **argv);
long long				current_time(void);
size_t					ft_strlen(const char *s);
unsigned long long		ft_atoull(const char *nptr);
long long				ft_atoll(const char *nptr);
int						overflows_long_long(char *str);
int						overflows_int(char *str);
t_data					*initializer(char **argv);
void					free_all(t_data *data);
void					the_creator(t_data *data);
