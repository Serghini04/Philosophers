/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:17:22 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/10 13:16:50 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

typedef struct s_philo t_philo;
typedef struct s_index_info t_index_info;

struct	s_philo
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	die;
	pthread_mutex_t	add;
	t_index_info	*info_philo;
	pthread_t		checker;
	size_t			s_time;
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				if_die;
	int				nb_meals;
};

struct s_index_info
{
	pthread_t	th;
	t_philo		*data;
	int			t_live;
	int			index;
	int			nb_eat;
};

t_philo	*parsing(int ac, char **av);
t_philo	*init_philo(t_philo	*data);
t_philo	*create_thread_check(t_philo *data);
long	ft_atoi(char *str);
size_t	my_time(void);
void	*check_die(t_philo	*data);
void 	*ft(void *info);
void	my_free(t_philo *data);
void	my_sleep(size_t	time, t_index_info *data);
void	print_msg(t_index_info *data, char *msg);

#endif