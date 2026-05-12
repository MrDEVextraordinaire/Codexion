/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itemlali <itemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 18:56:28 by itemlali          #+#    #+#             */
/*   Updated: 2026/05/12 06:36:45 by itemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/codexion.h"

void	*safe_print(void *arg)
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
	t_data	*data;

	if (!parsed_validated(argc, argv))
		return (1);

	data = initializer(argv);
	if (!data)
	{
		fprintf(stderr, "[Error] Initializer / Allocator error\n");
		return (2);
	}
	printf("\ninit works: %d\n", data->config.number_of_coders);


	free_all(data);
	return (0);
}


// segf 699999979
