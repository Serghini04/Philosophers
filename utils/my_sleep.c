/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:38:22 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/09 18:42:45 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	my_sleep(size_t	time, t_index_info *data)
{
	size_t	pos;

	(void)data;
	pos = my_time();
	while(my_time() - pos < time)
	{
		pthread_mutex_lock(&data->data->die);
		if (data->data->if_die == 0)
		{
			pthread_mutex_unlock(&data->data->die);
			return;
		}
		pthread_mutex_unlock(&data->data->die);
	}
}
