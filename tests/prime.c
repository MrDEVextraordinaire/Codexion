
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_data t_data;

typedef struct s_prof
{
	int prof_id;
	pthread_t prof;
	t_data *data;
}	t_prof;


typedef struct s_data
{
	int iteration;
	int N_profs;
	t_prof *all_profs;
	pthread_mutex_t	license;
	pthread_cond_t got_license;
}	t_data;

void	*routine(void	*args)
{
	t_prof *prof = (t_prof *)args;
	int		i;

	// pthread_mutex_lock(&prof->data->license);

	printf("thread %d is running to work\n", prof->prof_id);

	while (prof->prof_id != prof->data->iteration)
	{
		printf("thread %d tried to work\n", prof->prof_id);
		printf("during sleep iter is: %d\n",prof->data->iteration);
		pthread_cond_wait(&prof->data->got_license, &prof->data->license);
	}


	printf("thread %d is working\n", prof->prof_id);


	prof->data->iteration = (prof->data->iteration + 1) % prof->data->N_profs;
	printf("thread %d added +1 so now iter is: %d\n",prof->prof_id,prof->data->iteration);


	// pthread_mutex_unlock(&prof->data->license);

	printf("thread %d is broadcasting\n", prof->prof_id);

	pthread_cond_broadcast(&prof->data->got_license);
	return (NULL);
}

int	main(int argc, char**argv)
{
	int			i;
	int			n;
	t_data		*data;

	data = malloc(sizeof(t_data));
	data->N_profs = atoi(argv[1]);
	data->all_profs = malloc(sizeof(t_prof) * data->N_profs);
	data->iteration = 0;
	pthread_mutex_init(&data->license, NULL);
	pthread_cond_init(&data->got_license, NULL);
	i = 0;
	while (i < data->N_profs)
	{
		data->all_profs[i].prof_id = i;
		data->all_profs[i].data = data;
		pthread_create(&data->all_profs[i].prof, NULL, routine, &data->all_profs[i]);
		i++;
	}

	i = 0;
	while (i < data->N_profs)
	{
		pthread_join(data->all_profs[i].prof, NULL);
		i++;
	}
	return (0);
}
