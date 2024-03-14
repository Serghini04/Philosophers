/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 03:35:22 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/13 23:01:12 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	print_msg(t_index_info *data, char *msg)
{
	size_t	time;

	sem_wait(data->data->write);
	time = my_time() - data->data->s_time;
	if (data->data->if_die)
		printf("%ld		%d %s\n", time, data->index + 1, msg);
	sem_post(data->data->write);
}

int	taking_forks(t_index_info *data)
{

	sem_wait(data->data->forks);
	print_msg(data, "has taken a fork");
	if (data->data->nb_philo == 1)
		return (sem_post(data->data->forks), 0);
	sem_wait(data->data->forks);
	print_msg(data, "has taken a fork");
	return (1);
}

void	time_to_eating(t_index_info *data)
{
	print_msg(data, "is eating");
	data->t_live = my_time();
	data->nb_eat++;
	my_sleep(data->data->t_eat, data);
	sem_post(data->data->forks);
	sem_post(data->data->forks);
}

void	routine_bonus(t_index_info *data)
{
	while (1)
	{
		sem_wait(data->data->write);
		if (!data->data->if_die)
		{
			sem_post(data->data->write);
			exit(1);
		}
		sem_post(data->data->write);
		if (!taking_forks(data))
			exit(1);
		time_to_eating(data);
		if (data->nb_eat == data->data->nb_meals)
			return ;
		print_msg(data, "is sleeping");
		my_sleep(data->data->t_sleep, data);
		print_msg(data, "is thinking");
	}
}