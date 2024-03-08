/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:38:22 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/08 17:26:13 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	my_sleep(size_t	time, t_index_info *data)
{
	size_t	pos;

	(void)data;
	pos = my_time();
	while(my_time() - pos < time);
}
