/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:25:26 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/14 21:21:45 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

t_philo	*init_philo(t_philo *data)
{
	int	i;

	i = 0;
	data->info_philo = malloc(sizeof(t_index_info) * data->nb_philo);
	if (!data->info_philo)
		return (free(data), NULL);
	data->s_time = my_time();
	while (i < data->nb_philo)
	{
		data->info_philo[i].index = i;
		data->info_philo[i].nb_eat = 0;
		data->info_philo[i].data = data;
		data->info_philo[i].t_live = data->s_time;
		i++;
	}
	sem_unlink("forks");
	sem_unlink("write");
	data->forks = sem_open("forks", O_CREAT, 0644, data->nb_philo);
	if (data->forks == SEM_FAILED)
		(perror("sem forks: "), exit(1));
	data->write = sem_open("write", O_CREAT, 0644, 1);
	if (data->write == SEM_FAILED)
		(perror("sem write: "), exit(1));
	return (data);
}

void	*checker(void *info)
{
	t_index_info	*data;
	size_t			time;
	int				count;
	int				i;

	i = 0;
	count = 0;
	data = (t_index_info *)info;
	while (1)
	{
		time = my_time() - data->t_live;
		if (time >= (size_t)data->data->t_die && data->nb_eat != 0)
		{
			sem_wait(data->data->write);
			time = my_time() - data->data->s_time;
			printf("%zu		%d died\n", time, data->index + 1);
			exit(1);
		}
	}
	return (NULL);
}

void	  create_process_checker(t_philo *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->info_philo[i].pr = fork();
			if (data->info_philo[i].pr == -1)
				(perror("fork error: "), exit(1));
		if (data->info_philo[i].pr == 0)
		{
			pthread_create(&data->info_philo[i].th, NULL, checker, &data->info_philo[i]);
			pthread_detach(data->info_philo[i].th);
			routine_bonus(&data->info_philo[i]);
			break;
		}
	}
}
