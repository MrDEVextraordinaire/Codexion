/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itemlali <itemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 18:56:28 by itemlali          #+#    #+#             */
/*   Updated: 2026/05/17 19:07:37 by itemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

iteration index = 1

#include "./includes/codexion.h"

void	*safe_print(void *arg)
{
	t_coder *coder = (t_coder *) arg;
	pthread_mutex_t *print_lock;

	print_lock = &coder->data->print_lock;

	while(coder id != iteration index )
		pthread_cond_wait(&condition, &print_lock)
	pthread_mutex_lock(print_lock);

	printf("coder %d printing at %lldms\n" , coder->id, (current_time() - coder->data->start_time));




	pthread_mutex_unlock(print_lock);

	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!parsed_validated(argc, argv))
		return (1);
	data = initializer(argv);
	if (!data)
	{
		fprintf(stderr, "[Error] Initializer / Allocator error\n");
		return (2);
	}
	printf("\ninit works: %d\n", (data->config->number_of_coders));
	printf("\ncoder 6 id: %d\n", (data->coders[5].id));

	pthread_mutex_init(&data->print_lock, NULL);
	int i = 0;
	data->start_time = current_time();
	usleep(3000000);




	while (i < data->config->number_of_coders)
	{
		printf("reaches here\n" );
		pthread_create(&data->threads[i], NULL, safe_print, &data->coders[i]);
		i++;
	}


	pthread_cond_init(wakeupcond)

	if 
		pthread_cond_broadcast(&wakeupcond, printlock);

	pthread_mutex_destroy(&data->print_lock);
	i=0;
	while (i < data->config->number_of_coders)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}


	the_creator(data);
	free_all(data);
	return (0);
}

// segf 699999979
