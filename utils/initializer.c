/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itemlali <itemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 00:47:15 by itemlali          #+#    #+#             */
/*   Updated: 2026/08/03 19:18:22 by itemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

static t_data	*init_coders(t_data *data)
{
	int	i;

	data->coders = malloc(sizeof(t_coder) * data->config->number_of_coders);
	if (!data->coders)
	{
		clean_dongle_struct(data, data->config->number_of_coders);
		return (NULL);
	}
	i = 0;
	while (i < data->config->number_of_coders)
	{
		data->coders[i].id = i + 1;
		data->coders[i].last_compiled = data->start_time;
		printf("init coder %d last compiled %ld start time: %ld\n", data->coders[i].id, data->coders[i].last_compiled, data->start_time);
		data->coders[i].compile_count = 0;
		data->coders[i].left_dongle = &(data->dongles[i]);
		data->coders[i].right_dongle = &(
				data->dongles[(i + 1) % data->config->number_of_coders]);
		data->coders[i].data = data;
		i++;
	}
	return (data);
}

static t_data	*dongle_init_loop(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->config->number_of_coders)
	{
		data->dongles[i].id = i + 1;
		data->dongles[i].last_released = current_time();
		data->dongles[i].in_use = FALSE;
		data->dongles[i].heap_size = 0;
		data->dongles[i].min_heap = malloc(
				sizeof(t_coder_queue) * data->config->number_of_coders);
		if (!data->dongles[i].min_heap)
			return (destroy_partial_dongle(data, i, PHASE_NONE), NULL);
		if (pthread_mutex_init(&(data->dongles[i].dongle_lock), NULL) != 0)
			return (destroy_partial_dongle(data, i, PHASE_HEAP), NULL);
		else
		if (pthread_cond_init(&data->dongles[i].cond, NULL) != 0)
			return (destroy_partial_dongle(data, i, PHASE_MUTEX), NULL);
		else{

		}
		i++;
	}
	return (data);
}

static t_data	*init_dongles(t_data *data)
{
	int	i;

	data->dongles = malloc(sizeof(t_dongle) * data->config->number_of_coders);
	if (!data->dongles)
	{
		free(data->config);
		free(data->threads);
		free(data);
		return (NULL);
	}
	if (!dongle_init_loop(data))
		return (NULL);
	return (data);
}

static t_data	*config_initializer(char **argv, t_data *data)
{
	data->config = malloc(sizeof(t_config));
	if (!data->config)
	{
		free(data);
		return (NULL);
	}
	data->config->number_of_coders = atoi(argv[NUMBER_OF_CODERS_ARG]);
	data->config->time_to_burnout = ft_atol(argv[TIME_TO_BURNOUT_ARG]);
	data->config->time_to_compile = ft_atol(argv[TIME_TO_COMPILE_ARG]);
	data->config->time_to_debug = ft_atol(argv[TIME_TO_DEBUG_ARG]);
	data->config->time_to_refactor = ft_atol(argv[TIME_TO_REFACTOR_ARG]);
	data->config->number_of_compiles_required = ft_atol(
			argv[N_REQUIRED_COMPILES_ARG]);
	data->config->dongle_cooldown = ft_atol(argv[DONGLE_COOLDOWN_ARG]);
	data->config->scheduler = argv[SCHEDULER_ARG];
	return (data);
}

t_data	*initializer(char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->start_time = current_time();
	if (!config_initializer(argv, data))
		return (NULL);
	data->threads = malloc(sizeof(pthread_t) * data->config->number_of_coders);
	if (!data->threads)
	{
		free(data);
		free(data->config);
		return NULL;
	}
	if (!init_dongles(data))
		return (NULL);
	if (!init_coders(data))
		return (NULL);
	return (data);
}
