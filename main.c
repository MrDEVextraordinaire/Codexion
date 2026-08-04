/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itemlali <itemlali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 18:56:28 by itemlali          #+#    #+#             */
/*   Updated: 2026/08/04 14:22:23 by itemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/codexion.h"

void safe_print(t_coder *coder, char *action)
{
	pthread_mutex_lock(&coder->data->burnout_lock);
	if (coder->data->simulation_over == FALSE)
	{
		pthread_mutex_lock(&coder->data->print_lock);
		printf("%ld coder %d %s\n", (current_time() - coder->data->start_time), coder->id, action);
		pthread_mutex_unlock(&coder->data->print_lock);
	}
	pthread_mutex_unlock(&coder->data->burnout_lock);

}

int check_sim_over(t_data *data)
{
	int status;

	pthread_mutex_lock(&data->burnout_lock);
	status = data->simulation_over;
	pthread_mutex_unlock(&data->burnout_lock);
	return status;
}

void release_dongles(t_coder *coder)
{
	coder->left_dongle->last_released = current_time();
	coder->right_dongle->last_released = current_time();
	printf("coder %d released left dongle %d right dongle %d\n", coder->id, coder->left_dongle->id, coder->right_dongle->id);
	pthread_mutex_unlock(&coder->left_dongle->dongle_lock);
	pthread_mutex_unlock(&coder->right_dongle->dongle_lock);
}

void take_dongles(t_coder *coder)
{
	t_dongle *first;
	t_dongle *second;
	long rls_time_1st;
	long rls_time_2nd;
	
	if (coder->left_dongle->id < coder->right_dongle->id)
	{
		first = coder->left_dongle;
		second = coder->right_dongle;
	}
	else
	{
		first = coder->right_dongle;
		second = coder->left_dongle;
	}
	while(1)
	{
		pthread_mutex_lock(&first->dongle_lock);
		printf("coder %d took 1st rd%d checking 1st cd\n",coder->id, first->id);
		rls_time_1st = current_time() - first->last_released;
		printf("rls_time_1st: %ld < dgl cd: %ld \n", rls_time_1st, coder->data->config->dongle_cooldown);
		if (rls_time_1st < coder->data->config->dongle_cooldown)
		{
			printf("coder %d faced 1st rd%d cd: %ld\n",coder->id, first->id , ((coder->data->config->dongle_cooldown - rls_time_1st) * 1000));
			pthread_mutex_unlock(&first->dongle_lock);
			usleep((coder->data->config->dongle_cooldown - rls_time_1st) * 1000);
			continue;
		}
		pthread_mutex_lock(&second->dongle_lock);
		printf("coder %d took 2nd ld%d checking for 2nd cd\n",coder->id,second->id);
		rls_time_2nd = current_time() - second->last_released;
		if (rls_time_2nd < coder->data->config->dongle_cooldown)
		{
			pthread_mutex_unlock(&first->dongle_lock);
			pthread_mutex_unlock(&second->dongle_lock);
			printf("###########coder %d faced ld%d releasing rd%d ld%d > sleep for: %ld\n",coder->id, second->id ,first->id, second->id, ((coder->data->config->dongle_cooldown - rls_time_2nd) * 1000));
			usleep((coder->data->config->dongle_cooldown - rls_time_2nd) * 1000);
			continue;
		}
		break;
	}
}

void	*routine(void *arg)
{
	t_coder *coder;

	coder = (t_coder *) arg;

	if (coder->id % 2 == 0)
		usleep(1000);
	while(!check_sim_over(coder->data))
	{
		take_dongles(coder);
		safe_print(coder, "is compiling");
		pthread_mutex_lock(&coder->data->burnout_lock);
		coder->compile_count++;
		printf("coder %d will compile ld%d rd%d %dth time for %ld, he last compiled: %ld ago\n", coder->id,coder->left_dongle->id, coder->right_dongle->id ,coder->compile_count,coder->data->config->time_to_compile , current_time() - coder->last_compiled);
		coder->last_compiled = current_time();
		pthread_mutex_unlock(&coder->data->burnout_lock);
		usleep(coder->data->config->time_to_compile * 1000);
		release_dongles(coder);
		safe_print(coder, "is debugging");
		usleep(coder->data->config->time_to_debug * 1000);
		safe_print(coder, "is refactorin\n\n");
		usleep(coder->data->config->time_to_refactor * 1000);
	}
	return (NULL);
}

void* monitor_routine(void *args)
{
	t_data *data = (t_data *)args;
	int i;
	int all_compiled;

	while(1)
	{
		i = 0;
		pthread_mutex_lock(&data->burnout_lock);
		all_compiled = TRUE;
		while (i < data->config->number_of_coders)
		{
			if ((current_time() - data->coders[i].last_compiled) > data->config->time_to_burnout)
				{
					pthread_mutex_lock(&data->print_lock);
					printf("%ld %d burned out\n",current_time() - data->start_time, data->coders[i].id);
					pthread_mutex_unlock(&data->print_lock);
					data->simulation_over = TRUE;
					pthread_mutex_unlock(&data->burnout_lock);
					return (NULL);
				}
			if (data->coders[i].compile_count < data->config->number_of_compiles_required)
				all_compiled = FALSE;
			i++;
		}
		if (all_compiled == TRUE)
		{
			data->simulation_over = TRUE;
			pthread_mutex_unlock(&data->burnout_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&data->burnout_lock);
		usleep(1000);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int i;

	if (!parsed_validated(argc, argv))
		return (1);
	data = initializer(argv);
	if (!data)
	{
		fprintf(stderr, "[Error] Initializer / Allocator error\n");
		return (2);
	}
	pthread_mutex_init(&data->burnout_lock, NULL);
	pthread_mutex_init(&data->print_lock, NULL);
	data->simulation_over = 0;
	i = 0;
	data->start_time = current_time();
	while (i < data->config->number_of_coders)
	{
		pthread_create(&data->threads[i], NULL, routine, &data->coders[i]);
		i++;
	}
	pthread_create(&data->monitor, NULL, monitor_routine, data);
	i = 0;
	while (i < data->config->number_of_coders)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
	pthread_join(data->monitor ,NULL);
	pthread_mutex_destroy(&data->burnout_lock);
	pthread_mutex_destroy(&data->print_lock);
	free_all(data);
	return (0);
}

// segf 699999979
