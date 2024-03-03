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
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
	t_index_info	*info_philo;			
	pthread_t		checker;
	size_t			s_time;
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				if_die;
	int				meat;
};

struct s_index_info
{
	pthread_t	th;
	t_philo		*data;
	int			t_live;
	int			index;
};

t_philo	*parsing(int ac, char **av);
long	ft_atoi(char *str);
void	*ft(void *info);
size_t	my_time(void);
#endif