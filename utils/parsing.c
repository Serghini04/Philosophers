/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:19:33 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/07 20:51:04 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*check_input(int ac, char **av, t_philo *data)
{
	data = malloc(sizeof(t_philo));
	if (!data)
		return (NULL);
	data->nb_philo = ft_atoi(av[1]);
	if (data->nb_philo <= 0)
		return (printf("Error nb philo > 60 \n"), free(data), NULL);
	data->t_die = ft_atoi(av[2]);
	if (data->t_die < 60)
		return (printf("Error in t_die > 60 \n"), free(data), NULL);
	data->t_eat = ft_atoi(av[3]);
	if (data->t_eat < 60)
		return (printf("Error in t_eat > 60 \n"), free(data), NULL);
	data->t_sleep = ft_atoi(av[4]);
	if (data->t_sleep < 60)
		return (printf("Error in t_sleep > 60 \n"), free(data), NULL);
	if (ac == 6)
	{
		data->nb_meals = ft_atoi(av[5]);
		if (data->nb_meals <= 0)
			return (printf("Error in meat > 0\n"), free(data), NULL);
	}
	else
		data->nb_meals = -1;
	return (data);
}

t_philo	*parsing(int ac, char **av)
{
	t_philo	*data;

	data = NULL;
	if (ac != 5 && ac != 6)
	{
		printf("invalid arg :\n");
		printf("(philo) (time die) (time eat) (time sleep) op:(nb meat)\n");
		return (NULL);
	}
	data = check_input(ac, av, data);
	if (!data)
		return (NULL);
	data = init_philo(data);
	return (data);
}
