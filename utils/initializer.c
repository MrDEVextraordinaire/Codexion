/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itemlali <itemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 00:47:15 by itemlali          #+#    #+#             */
/*   Updated: 2026/05/12 06:57:42 by itemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

static void	*init_coders(t_data *data)
{
	int	i;

	data->coders = malloc(sizeof(t_coder) * data->config.number_of_coders);
	if (!data->coders)
		free_all(data);
	i = 0;
	while (i < data->config.number_of_coders)
	{
		data->coders[i].id = i + 1;
		data->coders[i].last_compiled = 0;
		data->coders[i].compile_count = 0;
		data->coders[i].left_dongle = &(data->dongles[i]);
		data->coders[i].right_dongle = &(
				data->dongles[(i + 1) % data->config.number_of_coders]);
		data->coders[i].data = data;
		i++;
	}
	return (data);
}

void	min_heap_fail_partial_free(t_data *data, int i)
{
	while (--i >= 0)
	{
		free(data->dongles[i].min_heap);
		pthread_mutex_destroy(&(data->dongles[i].dongle_lock));
	}
	free(data->dongles);
}

static void	*init_dongles(t_data *data)
{
	int	i;

	data->dongles = malloc(sizeof(t_dongle) * data->config.number_of_coders);
	if (!data->dongles)
		return (NULL);
	i = 0;
	while (i < data->config.number_of_coders)
	{
		data->dongles[i].last_released = 0;
		data->dongles[i].in_use = FALSE;
		data->dongles[i].min_heap = malloc(
				sizeof(t_coder_queue) * data->config.number_of_coders);
		if (!data->dongles[i].min_heap)
		{
			min_heap_fail_partial_free(data, i);
			return (NULL);
		}
		pthread_mutex_init(&(data->dongles[i].dongle_lock), NULL);
		data->dongles[i].heap_size = 0;
		i++;
	}
	return (data);
}

static void	config_initializer(char **argv, t_data *data)
{
	data->config.number_of_coders = atoi(argv[NUMBER_OF_CODERS_ARG]);
	data->config.time_to_burnout = ft_atoll(argv[TIME_TO_BURNOUT_ARG]);
	data->config.time_to_compile = ft_atoll(argv[TIME_TO_COMPILE_ARG]);
	data->config.time_to_debug = ft_atoll(argv[TIME_TO_DEBUG_ARG]);
	data->config.time_to_refactor = ft_atoll(argv[TIME_TO_REFACTOR_ARG]);
	data->config.number_of_compiles_required = ft_atoll(
			argv[N_REQUIRED_COMPILES_ARG]);
	data->config.dongle_cooldown = ft_atoll(argv[DONGLE_COOLDOWN_ARG]);
	data->config.scheduler = argv[SCHEDULER_ARG];
}

t_data	*initializer(char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	config_initializer(argv, data);
	if (!init_dongles(data))
	{
		free(data);
		return (NULL);
	}
	if (!init_coders(data))
		return (NULL);
	return (data);
}

