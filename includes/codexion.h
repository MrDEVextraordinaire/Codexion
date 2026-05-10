/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itemlali <itemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 18:56:14 by itemlali          #+#    #+#             */
/*   Updated: 2026/05/10 01:39:10 by itemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <limits.h>


typedef struct s_dongle	t_dongle;
typedef struct s_data	t_data;
typedef struct s_waiter	t_waiter;

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
	long long			last_released;
	t_waiter			*heap;
	int					heap_size;
	int					heap_cap;

}						t_dongle;

typedef struct s_waiter
{
	int					coder_id;
	long long			deadline;
	long long			request_time;
	pthread_cond_t		cond;
}						t_waiter;

typedef struct s_data
{
	t_config			config;
	t_coder				*coders;
	t_dongle			*dongles;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		death_lock;
	pthread_t			*threads;
	pthread_t			monitor;
	long long			start_time;
	int					simulation_over;
}						t_data;

int						ft_isdigit(char c);
int						parsed_validated(int argc, char **argv);
long long				current_time(void);
int						valid_int(char *str);
int						valid_long_long(char *str);
size_t					ft_strlen(const char *s);
unsigned long long		ft_atoull(const char *nptr);
int						overflows_long_long(char *str);
int						overflows_int(char *str);
