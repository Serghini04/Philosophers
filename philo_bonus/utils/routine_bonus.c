/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 03:35:22 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/15 22:40:48 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	print_msg(t_index_info *data, char *msg)
{
	size_t	time;

	sem_wait(data->data->write);
	time = my_time() - data->data->s_time;
	printf("%ld		%d %s\n", time, data->index + 1, msg);
	sem_post(data->data->write);
}

void	taking_forks(t_index_info *data)
{
	sem_wait(data->data->forks);
	print_msg(data, "has taken a fork");
	sem_wait(data->data->forks);
	print_msg(data, "has taken a fork");
}

void	time_to_eating(t_index_info *data)
{
	print_msg(data, "is eating");
	data->t_live = my_time();
	data->nb_eat++;
	my_sleep(data->data->t_eat);
	sem_post(data->data->forks);
	sem_post(data->data->forks);
}

void	routine_bonus(t_index_info *data)
{
	while (1)
	{
		taking_forks(data);
		time_to_eating(data);
		if (data->nb_eat == data->data->nb_meals)
			exit(0);
		print_msg(data, "is sleeping");
		my_sleep(data->data->t_sleep);
		print_msg(data, "is thinking");
	}
}
