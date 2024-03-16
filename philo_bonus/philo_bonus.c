/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:27:02 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/16 00:45:14 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_philo	*data;
	int		i;
	int		s;

	i = 0;
	data = parsing(ac, av);
	if (!data)
		return (-1);
	create_process_checker(data);
	while (waitpid(-1, &s, 0) != -1)
	{
		s = WEXITSTATUS(s);
		if (s)
		{
			i = -1;
			while (++i < data->nb_philo)
				kill(data->info_philo[i].pr, SIGQUIT);
		}
	}
	sem_close(data->write);
	sem_close(data->forks);
	my_free(data);
	return (0);
}
