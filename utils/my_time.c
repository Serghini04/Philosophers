#include "../philo.h"

size_t	my_time(void)
{
	struct  timeval time;

	if (gettimeofday(&time, NULL) == -1)
		write(1, "Error gettimeofday\n", 19);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
