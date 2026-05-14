/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itemlali <itemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 04:55:50 by itemlali          #+#    #+#             */
/*   Updated: 2026/05/14 04:46:48 by itemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"


void	clean_dongle_struct(t_data *data, int i)
{
	while (--i >= 0)
	{
		free(data->dongles[i].min_heap);
		pthread_mutex_destroy(&(data->dongles[i].dongle_lock));
		pthread_cond_destroy(&data->dongles[i].cond);
	}
	free(data->dongles);
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
		pthread_cond_destroy(&data->dongles[i].cond);
		i++;
	}
	free(data->dongles);
	data->dongles = NULL;
	free(data->config);
	data->config = NULL;
	free(data);
	data = NULL;
}
