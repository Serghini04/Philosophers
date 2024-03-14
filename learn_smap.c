#include "philo_bonus/philo_bonus.h"

sem_t *s;

void	*ft(void *data)
{
	printf("i'm checker for process %d\n", getpid());
	return (NULL);
}

int main()
{
	pthread_t th[2];
	int i = -1;
	int p[2];
	while (++i < 2)
	{
		p[i] = fork();
		printf(">> hi process is here\n");
		if (p[i] != 0)
			exit(1);
	}
	i = -1;
	while (++i < 2)
	{
		if (p[i] == 0)
		{
			pthread_create(&th[i], NULL, ft, NULL);
			pthread_detach(th[i]);
		}
	}
}