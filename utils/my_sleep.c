/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:38:22 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/11 14:55:56 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	my_sleep(size_t	time, t_index_info *data)
{
	size_t	pos;

	pos = my_time();
	while (my_time() - pos < time)
	{
		pthread_mutex_lock(&data->data->write);
		if (data->data->if_die == 0)
		{
			pthread_mutex_unlock(&data->data->write);
			return ;
		}
		pthread_mutex_unlock(&data->data->write);
	}
}
