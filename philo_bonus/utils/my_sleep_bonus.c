/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_sleep_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:49:21 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/13 22:22:40 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	my_sleep(size_t	time, t_index_info *data)
{
	size_t	pos;

	pos = my_time();
	while (my_time() - pos < time)
	{
		sem_wait(data->data->write);
		if (data->data->if_die == 0)
		{
			sem_post(data->data->write);
			return ;
		}
		sem_post(data->data->write);
		usleep(100);
	}
}