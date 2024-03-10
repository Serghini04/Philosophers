/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:32:35 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/10 13:50:07 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_msg(t_index_info *data, char *msg)
{
	size_t	time;

	// pthread_mutex_lock(&data->data->write);
	pthread_mutex_lock(&data->data->die);
	time = my_time() - data->data->s_time;
	if (data->data->if_die)
		printf("%ld		%d %s\n", time, data->index + 1, msg);
	pthread_mutex_unlock(&data->data->die);
	// pthread_mutex_unlock(&data->data->write);
}

void	taking_forks(t_index_info *data)
{
	pthread_mutex_lock(&data->data->forks[data->index]);
	print_msg(data, "has taken a fork");
}
void	time_to_eating(t_index_info *data)
{
	print_msg(data, "is eating");
	pthread_mutex_lock(&data->data->die);
	data->t_live = my_time() - data->data->s_time;
	pthread_mutex_unlock(&data->data->die);
	pthread_mutex_lock(&data->data->add);
	data->nb_eat++;
	pthread_mutex_unlock(&data->data->add);
	my_sleep(data->data->t_eat, data);
	pthread_mutex_unlock(&data->data->forks[data->index]);
	pthread_mutex_unlock(&data->data->forks[(data->index + 1) % data->data->nb_philo]);
}

void *ft(void *info)
{
	t_index_info	*data;

	data = (t_index_info *)info;
	while (1)
	{

		taking_forks(data);
		if (data->data->nb_philo == 1)
			break;
		pthread_mutex_lock(&data->data->forks[(data->index + 1) % data->data->nb_philo]);
		print_msg(data, "has taken a fork");
		time_to_eating(data);
		pthread_mutex_lock(&data->data->write);
		if (data->nb_eat == data->data->nb_meals)
			return (pthread_mutex_unlock(&data->data->write), NULL);
		pthread_mutex_unlock(&data->data->write);
		print_msg(data, "is sleeping");
		my_sleep(data->data->t_sleep, data);
		print_msg(data, "is thinking");
		pthread_mutex_lock(&data->data->die);
		if (data->data->if_die == 0)
		{
			pthread_mutex_unlock(&data->data->die);
			return (NULL);
		}
		pthread_mutex_unlock(&data->data->die);
	}
	return (NULL);
}
