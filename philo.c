/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:18:46 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/07 21:36:25 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_die(void	*info)
{
	t_philo	*data;
	int		time;
	int		i;
	int		cout;

	data = (t_philo *)info;
	while (data->if_die)
	{
		i = 0;
		cout = 0;
		while (i < data->nb_philo)
		{
			time = data->info_philo[i].t_live - (my_time() - data->s_time);
			if (data->nb_meals == data->info_philo[i].nb_eat)
				cout++;
			if (time <= 0)
			{
				printf("%ld		%d died\n", my_time() - data->s_time, i + 1);
				data->if_die = 0;
				return NULL;
			}
			if (data->nb_philo == cout)
			{
				data->if_die = 0;
				return NULL;
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
	while (data->data->if_die)
	{
		if (data->data->if_die)
			printf("%ld		%d is thinking\n", my_time() - data->data->s_time, data->index + 1);
		pthread_mutex_lock(&data->data->forks[data->index]);
		if (data->data->if_die)
			printf("%ld		%d has taken a fork\n", my_time() - data->data->s_time, data->index + 1);
		if (data->data->nb_philo == 1)
		{
			usleep(data->data->t_die * 1000);
			break;
		}
		if (data->data->if_die)
			printf("%ld		%d is thinking\n", my_time() - data->data->s_time, data->index + 1);
		pthread_mutex_lock(&data->data->forks[(data->index + 1) % data->data->nb_philo]);
		if (data->data->if_die)
		{
			printf("%ld		%d has taken a fork\n", my_time() - data->data->s_time, data->index + 1);
			printf("%ld		%d is eating\n", my_time() - data->data->s_time, data->index + 1);
			data->t_live += data->data->t_die;
			data->nb_eat++;
			usleep(data->data->t_eat * 1000);
		}
		pthread_mutex_unlock(&data->data->forks[data->index]);
		pthread_mutex_unlock(&data->data->forks[(data->index + 1) % data->data->nb_philo]);
		if (data->data->if_die)
		printf("%ld		%d is sleeping\n", my_time() - data->data->s_time, data->index + 1);
		if (data->data->if_die)
		usleep(data->data->t_sleep * 1000);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo	*data;
	int		i;

	i = 0;
	data = parsing(ac, av);
	if (!data)
		return (-1);
	data = create_thread_check(data);
	if (!data)
		return (-1);
	while (i < data->nb_philo)
	{
		if (pthread_join(data->info_philo[i].th, NULL) != 0)
			return (my_free(data), -1);
		i++;
	}
	system("leaks philo");
	return (0);
}
