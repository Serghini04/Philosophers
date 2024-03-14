/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:18:46 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/13 20:54:23 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	count_if_die(t_philo *data, int count, int i)
{
	size_t	time;

	if (data->nb_philo == count)
		return (1);
	time = my_time() - data->info_philo[i].t_live;
	if (time >= (size_t)data->t_die)
	{
		pthread_mutex_lock(&data->write);
		printf("%zu		%d died\n", time, data->info_philo[i].index + 1);
		data->if_die = 0;
		pthread_mutex_unlock(&data->write);
		return (1);
	}
	return (0);
}

void	check_die(t_philo *data)
{
	int		i;
	int		count;

	while (1)
	{
		i = 0;
		count = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->info_philo[i].add);
			if (data->nb_meals == data->info_philo[i].nb_eat)
				count++;
			if (count_if_die(data, count, i))
			{
				pthread_mutex_unlock(&data->info_philo[i].add);
				return ;
			}
			pthread_mutex_unlock(&data->info_philo[i].add);
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	t_philo	*data;
	int		i;

	i = 0;
	data = parsing(ac, av);
	if (!data)
		return (-1);
	if (!create_thread_check(data))
		return (-1);
	my_free(data);
	return (0);
}
