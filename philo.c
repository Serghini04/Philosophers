#include "philo.h"

void *ft(void *info)
{
	t_index_info	*data;
	int				v_eat;

	v_eat = 2;
	data = (t_index_info *)info;
	while (v_eat)
	{
		pthread_mutex_lock(&data->data->forks[(data->index + 1) % data->data->nb_philo]);
		printf("time	%d has taken a forks\n", data->index + 1);
		pthread_mutex_lock(&data->data->forks[data->index]);
		printf("time	%d has taken a forks\n", data->index + 1);
		printf("time	%d is eating\n", data->index + 1);
		usleep(data->data->t_eat * 1000);
		pthread_mutex_unlock(&data->data->forks[data->index]);
		pthread_mutex_unlock(&data->data->forks[(data->index + 1) % data->data->nb_philo]);
		printf("time	%d is sleeping\n", data->index + 1);
		usleep(data->data->t_sleep * 1000);
		printf("time	%d id thinking\n", data->index + 1);
		v_eat--;
	}
	return NULL;
}

int	main(int ac, char **av)
{
	t_philo	*data;
	int		i;

	i = 0;
	data = parsing(ac, av);
	if (!data)
		return (-1);
	while (i < data->nb_philo)
	{
		pthread_create(&data->info_philo[i].th, NULL, ft, &data->info_philo[i]);
		usleep(10);
		i++;
	}
	i = 0;
	while (i <data->nb_philo)
	{
		pthread_join(data->info_philo[i].th, NULL);
		i++;
	}
	return (0);
}
