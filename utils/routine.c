/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:32:35 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/09 13:29:59 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_msg(t_index_info *data, char *msg)
{
	size_t	time;

	pthread_mutex_lock(&data->data->write);
	time = my_time() - data->data->s_time;
	pthread_mutex_lock(&data->data->add);
	if (data->data->if_die)
		printf("%ld		%d %s", time, data->index + 1, msg);
	pthread_mutex_unlock(&data->data->add);
	pthread_mutex_unlock(&data->data->write);
}
