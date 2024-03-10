/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:18:46 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/10 17:23:39 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_die(t_philo	*data)
{
	int		time;
	int		i;
	int		count;

	while (1)
	{
		i = 0;
		count = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->add);
			if (data->nb_meals == data->info_philo[i].nb_eat)
				count++;
			pthread_mutex_unlock(&data->add);
			if (data->nb_philo == count)
			{
				pthread_mutex_lock(&data->die);
				data->if_die = 0;
				pthread_mutex_unlock(&data->die);
				return NULL;
			}
			pthread_mutex_lock(&data->die);
			time = (my_time() - data->s_time) - data->info_philo[i].t_live;
			pthread_mutex_unlock(&data->die);
			if (time >= data->t_die)
			{
				print_msg(&data->info_philo[i], "died");
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
