#include "../philo.h"

t_philo *parsing(int ac, char **av)
{
	t_philo	*data;
	int		i;	
	i = 0;
	if (ac != 5 && ac != 6)
	{
	    write(2, "invalid arg : (philo) (time die) (time eat) (time sleep) op:(time meat)\n", 72);
		return (NULL);
	}
	data = malloc(sizeof(t_philo));
	if (!data)
		return (NULL);
	data->nb_philo = ft_atoi(av[1]);
	if (data->nb_philo <= 0)
		return (write(1, "Error nb philo\n", 15), free(data), NULL);
	data->t_die = ft_atoi(av[2]);
	if (data->t_die < 60)
	{
	    write(2, "Error in t_die\n", 15);
	    return (free(data), NULL);
	}
	data->t_eat = ft_atoi(av[3]);
	if (data->t_eat < 60)
	    return (write(2, "Error in t_eat\n", 15), free(data), NULL);
	data->t_sleep = ft_atoi(av[4]);
	if (data->t_sleep < 60)
	    return (write(2, "Error in t_sleep\n", 17), free(data), NULL);
	if (ac == 6)
	{
		data->meat = ft_atoi(av[5]);
		if (data->meat <= 0)
		    return (write(2, "Error in meat\n", 15), free(data), NULL);
	}
	else
		data->meat = -1;
	data->info_philo = malloc(sizeof(t_index_info) * data->nb_philo);
	if (!data->info_philo)
		return (free(data), NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (free(data->info_philo), free(data), NULL);
	pthread_mutex_init(&data->mutex, NULL);
	while (i < data->nb_philo)
	{
		data->info_philo[i].index = i;
		data->info_philo[i].data = data;
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (data);
}
