/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:18:46 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/11 14:32:41 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_die(t_philo	*data)
{
	size_t		time;
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
			if (data->nb_philo == count)
			{
				pthread_mutex_lock(&data->write);
				data->if_die = 0;
				pthread_mutex_unlock(&data->write);
				pthread_mutex_unlock(&data->info_philo[i].add);
				return NULL;
			}
			time = my_time() - data->info_philo[i].t_live;
			if (time >= (size_t)data->t_die)
			{
				pthread_mutex_lock(&data->write);
				data->if_die = 0;
				printf("%zu		%d died\n", time, data->info_philo[i].index + 1);
				pthread_mutex_unlock(&data->write);
				pthread_mutex_unlock(&data->info_philo[i].add);
				return NULL;
			}
			pthread_mutex_unlock(&data->info_philo[i].add);
			i++;
		}
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
	if (!create_thread_check(data))
		return (-1);
	while (i < data->nb_philo)
	{
		if (pthread_join(data->info_philo[i].th, NULL) != 0)
			return (my_free(data), -1);
		i++;
	}
	return (0);
}
