/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:32:35 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/11 22:37:32 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_msg(t_index_info *data, char *msg)
{
	size_t	time;

	pthread_mutex_lock(&data->data->write);
	time = my_time() - data->data->s_time;
	if (data->data->if_die)
		printf("%ld		%d %s\n", time, data->index + 1, msg);
	pthread_mutex_unlock(&data->data->write);
}

int	taking_forks(t_index_info *data)
{
	int	index_fork;

	index_fork = (data->index + 1) % data->data->nb_philo;
	pthread_mutex_lock(&data->data->forks[data->index]);
	print_msg(data, "has taken a fork");
	if (data->data->nb_philo == 1)
		return (0);
	pthread_mutex_lock(&data->data->forks[index_fork]);
	print_msg(data, "has taken a fork");
	return (1);
}

void	time_to_eating(t_index_info *data)
{
	int	index_fork;

	index_fork = (data->index + 1) % data->data->nb_philo;
	print_msg(data, "is eating");
	pthread_mutex_lock(&data->add);
	data->t_live = my_time();
	data->nb_eat++;
	pthread_mutex_unlock(&data->add);
	my_sleep(data->data->t_eat, data);
	pthread_mutex_unlock(&data->data->forks[data->index]);
	pthread_mutex_unlock(&data->data->forks[index_fork]);
}

void	*ft(void *info)
{
	t_index_info	*data;

	data = (t_index_info *)info;
	while (1)
	{
		pthread_mutex_lock(&data->data->write);
		if (data->data->if_die == 0)
			return (pthread_mutex_unlock(&data->data->write), NULL);
		pthread_mutex_unlock(&data->data->write);
		if (!taking_forks(data))
			return (NULL);
		time_to_eating(data);
		if (data->nb_eat == data->data->nb_meals)
			return (NULL);
		print_msg(data, "is sleeping");
		my_sleep(data->data->t_sleep, data);
		print_msg(data, "is thinking");
	}
	return (NULL);
}
