/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itemlali <itemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 04:55:50 by itemlali          #+#    #+#             */
/*   Updated: 2026/08/09 18:21:49 by itemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"


void	destroy_partial_dongle(t_data *data, int i, t_init_phase phase)
{
	if (phase >= PHASE_HEAP)
		free(data->dongles[i].min_heap);
	if (phase >= PHASE_MUTEX)
		pthread_mutex_destroy(&(data->dongles[i].dongle_lock));
	if (phase >= PHASE_FULL)
		pthread_cond_destroy(&data->dongles[i].dongle_available);
	clean_dongle_struct(data, i);
}

void	clean_dongle_struct(t_data *data, int i)
{
	while (--i >= 0)
	{
		free(data->dongles[i].min_heap);
		pthread_mutex_destroy(&(data->dongles[i].dongle_lock));
		pthread_cond_destroy(&data->dongles[i].dongle_available);
	}
	free(data->dongles);
	free(data->threads);
	free(data->config);
	free(data);
}

void	free_all(t_data *data)
{
	int	i;

	free(data->coders);
	data->coders = NULL;
	i = 0;
	while (i < data->config->number_of_coders)
	{
		free(data->dongles[i].min_heap);
		data->dongles[i].min_heap = NULL;
		pthread_mutex_destroy(&(data->dongles[i].dongle_lock));
		pthread_cond_destroy(&data->dongles[i].dongle_available);
		i++;
	}
	free(data->dongles);
	free(data->threads);
	free(data->config);
	free(data);
}
