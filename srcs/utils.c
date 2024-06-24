/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:30:45 by vdomasch          #+#    #+#             */
/*   Updated: 2024/06/24 14:20:30 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_destroy(t_data *data, bool destroy)
{
	int	i;

	i = 0;
	if (destroy)
	{
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->philo[i].left_fork);
			i++;
		}
	}
	free(data->thread);
	free(data->philo);
	pthread_mutex_destroy(&data->m_philo);
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_ready);
	pthread_mutex_destroy(&data->m_data);
}

void	ft_usleep(time_t time)
{
	time_t	start;

	start = get_time();
	while (get_time() < start + time)
		usleep(100);
}

time_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
