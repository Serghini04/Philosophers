/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:17:22 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/12 18:21:52 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_index_info	t_index_info;
typedef struct s_philo		t_philo;

struct	s_philo
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
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
	pthread_mutex_t	add;
	pthread_t		th;
	t_philo			*data;
	size_t			t_live;
	int				index;
	int				nb_eat;
};

t_philo	*parsing(int ac, char **av);
t_philo	*init_philo(t_philo	*data);
t_philo	*create_thread_check(t_philo *data);
size_t	my_time(void);
long	ft_atoi(char *str);
void	*ft(void *info);
void	check_die(t_philo	*data);
void	my_free(t_philo *data);
void	my_sleep(size_t	time, t_index_info *data);
void	print_msg(t_index_info *data, char *msg);

#endif