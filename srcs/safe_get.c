/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:31:37 by vdomasch          #+#    #+#             */
/*   Updated: 2024/06/24 12:41:19 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	safely_get_bool(pthread_mutex_t *mutex, bool *value)
{
	int	result;

	pthread_mutex_lock(mutex);
	result = *value;
	pthread_mutex_unlock(mutex);
	return (result);
}

int	safely_get_int(pthread_mutex_t *mutex, int *value)
{
	int	result;

	pthread_mutex_lock(mutex);
	result = *value;
	pthread_mutex_unlock(mutex);
	return (result);
}

time_t	safely_get_time(pthread_mutex_t *mutex, time_t *value)
{
	size_t	result;

	pthread_mutex_lock(mutex);
	result = *value;
	pthread_mutex_unlock(mutex);
	return (result);
}

void	safe_print(t_philo *philo, const char *str, int id)
{
	pthread_mutex_lock(&philo->data->m_print);
	if (!safely_get_bool(&philo->data->m_data, &philo->data->is_dead))
		printf("%ld %d %s\n", get_time() - philo->data->start_time, id, str);
	pthread_mutex_unlock(&philo->data->m_print);
}
