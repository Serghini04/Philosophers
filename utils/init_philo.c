/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:22:49 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/07 21:27:21 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*init_philo(t_philo	*data)
{
	int	i;

	i = 0;
	data->info_philo = malloc(sizeof(t_index_info) * data->nb_philo);
	if (!data->info_philo)
		return (free(data), NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (free(data->info_philo), free(data), NULL);
	while (i < data->nb_philo)
	{
		data->info_philo[i].index = i;
		data->info_philo[i].data = data;
		data->info_philo[i].t_live = data->t_die;
		data->info_philo[i].nb_eat = 0;
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (my_free(data), NULL);
		i++;
	}
	data->s_time = my_time();
	data->if_die = 1;
	return (data);
}

t_philo	*create_thread_check(t_philo *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->info_philo[i].th, NULL, \
								ft, &data->info_philo[i]) != 0)
			return (my_free(data), NULL);
		usleep(50);
		i++;
	}
	if (pthread_create(&data->checker, NULL, check_die, data) != 0)
		return (my_free(data), NULL);
	if (pthread_join(data->checker, NULL) != 0)
		return (my_free(data), NULL);
	return (data);
}
