/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:30:45 by vdomasch          #+#    #+#             */
/*   Updated: 2024/06/22 15:42:44 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

time_t	get_time(void)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}