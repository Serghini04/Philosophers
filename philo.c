#include "philo.h"

void	*check_die(void	*info)
{
	t_philo	*data;
	int				time;
	int				i;

	data = (t_philo *)info;
	while (data->if_die)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			time = data->info_philo[i].t_live - (my_time() - data->s_time);
			if (time <= 0)
			{
				printf("%ld		%d died\n", my_time() - data->s_time, i + 1);
				data->if_die = 0;
				return NULL;
				//exit(1);
				//my_clean(data);
			}
			usleep(100);
			i++;
		}
	}
	return (NULL);
}

void *ft(void *info)
{
	t_index_info	*data;

	data = (t_index_info *)info;
	while (data->data->if_die == 1)
	{

		pthread_mutex_lock(&data->data->forks[data->index]);
		if (data->data->if_die)
			printf("%ld		%d has taken a forks\n", my_time() - data->data->s_time, data->index + 1);
		if (data->data->nb_philo == 1)
		{
			usleep(data->data->t_die * 1000);
			break;
		}
		pthread_mutex_lock(&data->data->forks[(data->index + 1) % data->data->nb_philo]);
		if (data->data->if_die)
		{
			printf("%ld		%d has taken a forks\n", my_time() - data->data->s_time, data->index + 1);
			printf("%ld		%d is eating\n", my_time() - data->data->s_time, data->index + 1);
			data->t_live += data->data->t_die;
			usleep(data->data->t_eat * 1000);
		}
		pthread_mutex_unlock(&data->data->forks[data->index]);
		pthread_mutex_unlock(&data->data->forks[(data->index + 1) % data->data->nb_philo]);
		if (data->data->if_die)
		printf("%ld		%d is sleeping\n", my_time() - data->data->s_time, data->index + 1);
		if (data->data->if_die)
		usleep(data->data->t_sleep * 1000);
		if (data->data->if_die)
		printf("%ld		%d id thinking\n", my_time() - data->data->s_time, data->index + 1);
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
		usleep(50);
		i++;
	}
	i = 0;
	check_die(data);
	while (i <data->nb_philo)
	{
		pthread_join(data->info_philo[i].th, NULL);
		i++;
	}
	return (0);
}
