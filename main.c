/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itemlali <itemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 18:56:28 by itemlali          #+#    #+#             */
/*   Updated: 2026/05/10 02:43:21 by itemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/codexion.h"
#include <unistd.h>

void	*atomic_print(void *arg)
{
	t_coder			*coder;
	pthread_mutex_t	*print_lock;

	coder = (t_coder *)arg;
	usleep(coder->id * 1000);
	print_lock = &coder->data->print_lock;
	pthread_mutex_lock(print_lock);
	printf("\ncoder N%d ", coder->id);
	printf("printing at %lldms\n", (current_time() - coder->data->start_time));

	pthread_mutex_unlock(print_lock);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_config	config;
	t_coder		*coders;
	pthread_t	*threads;

	// t_dongle dongle;
	if (!parsed_validated(argc, argv))
		return (1);
	config.number_of_coders = atoi(argv[1]);
	coders = malloc(sizeof(t_coder) * config.number_of_coders);
	threads = malloc(sizeof(pthread_t) * config.number_of_coders);
	if (!coders || !threads)
	{
		printf("too much to allocate");
		return(0);
	}

	// t_dongle *dongles = malloc(sizeof(t_dongle) * config.number_of_coders);
	data.start_time = current_time();
	pthread_mutex_init(&data.print_lock, NULL);
	for (int i = 0; i < config.number_of_coders; i++)
	{
		coders[i].id = i;
		coders[i].data = &data;
		pthread_create(&threads[i], NULL, atomic_print, &coders[i]);
	}
	for (int i = 0; i < config.number_of_coders; i++)
		pthread_join(threads[i], NULL);
	free(coders);
	free(threads);
	return (0);
}


// segf 699999979
