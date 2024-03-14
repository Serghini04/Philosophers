/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:27:25 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/13 22:21:09 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
#include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>

typedef struct s_index_info	t_index_info;

typedef struct s_philo
{
	t_index_info	*info_philo;
	sem_t			*forks;
	sem_t			*write;
	size_t			s_time;
	int				nb_philo;
	int				t_die;
	int				if_die;
	int				t_eat;
	int				t_sleep;
	int				nb_meals;
}	t_philo;

struct s_index_info
{
	pthread_t	th;
	t_philo		*data;
	size_t		t_live;
	pid_t		pr;
	int			index;
	int			nb_eat;
};

void	my_sleep(size_t	time, t_index_info *data);
void	create_process_checker(t_philo *data);
void	routine_bonus(t_index_info *data);
t_philo	*parsing(int ac, char **av);
size_t	my_time(void);
long	ft_atoi(char *str);
t_philo	*init_philo(t_philo *data);
#endif