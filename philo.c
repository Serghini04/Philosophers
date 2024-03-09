/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:18:46 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/09 18:42:03 by meserghi         ###   ########.fr       */
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
	while (1)
	{
		i = 0;
		cout = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->die);
			time = data->info_philo[i].t_live - (my_time() - data->s_time);
			pthread_mutex_unlock(&data->die);
			pthread_mutex_lock(&data->add);
			if (data->nb_meals == data->info_philo[i].nb_eat)
				cout++;
			pthread_mutex_unlock(&data->add);
			if (time <= 0)
			{
				print_msg(&data->info_philo[i], "died\n");
				pthread_mutex_lock(&data->die);
				data->if_die--;
				pthread_mutex_unlock(&data->die);
				return NULL;
			}
			if (data->nb_philo == cout)
			{
				pthread_mutex_lock(&data->die);
				data->if_die = 0;
				pthread_mutex_unlock(&data->die);
				return NULL;
			}
			i++;
		}
		pthread_mutex_lock(&data->die);
		if (!data->if_die)
		{
			pthread_mutex_unlock(&data->die);
			return (NULL);
		}
		pthread_mutex_unlock(&data->die);
	}
	return (NULL);
}

void *ft(void *info)
{
	t_index_info	*data;

	data = (t_index_info *)info;
	while (1)
	{
		pthread_mutex_lock(&data->data->forks[data->index]);
		print_msg(data, "has taken a fork\n");
		if (data->data->nb_philo == 1)
		{
			my_sleep(data->data->t_die, data);
			break;
		}
		pthread_mutex_lock(&data->data->forks[(data->index + 1) % data->data->nb_philo]);
		print_msg(data, "has taken a fork\n");
		print_msg(data, "is eating\n");
		my_sleep(data->data->t_eat, data);
		pthread_mutex_lock(&data->data->die);
		data->t_live += data->data->t_die;
		pthread_mutex_unlock(&data->data->die);
		pthread_mutex_lock(&data->data->add);
		data->nb_eat++;
		pthread_mutex_unlock(&data->data->add);
		print_msg(data, "is thinking\n");
		pthread_mutex_unlock(&data->data->forks[data->index]);
		pthread_mutex_unlock(&data->data->forks[(data->index + 1) % data->data->nb_philo]);
		print_msg(data, "is sleeping\n");
		my_sleep(data->data->t_sleep, data);
		pthread_mutex_lock(&data->data->die);
		if (data->data->if_die == 0)
		{
			pthread_mutex_unlock(&data->data->die);
			break;
		}
		pthread_mutex_unlock(&data->data->die);
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
	//system("leaks philo");
	return (0);
}
