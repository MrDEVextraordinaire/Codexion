/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itemlali <itemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 04:55:50 by itemlali          #+#    #+#             */
/*   Updated: 2026/05/12 06:53:20 by itemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

void	free_all(t_data *data)
{
	int	i;

	free(data->coders);
	data->coders = NULL;
	i = 0;
	while (i < data->config.number_of_coders)
	{
		free(data->dongles[i].min_heap);
		data->dongles[i].min_heap = NULL;
		pthread_mutex_destroy(&(data->dongles[i].dongle_lock));
		i++;
	}
	free(data->dongles);
	data->dongles = NULL;
	free(data);
	data = NULL;
}
