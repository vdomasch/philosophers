/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:31:37 by vdomasch          #+#    #+#             */
/*   Updated: 2024/06/23 12:43:33 by vdomasch         ###   ########.fr       */
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

void	safely_set_bool(pthread_mutex_t *mutex, bool *value, bool new)
{
	pthread_mutex_lock(mutex);
	*value = new;
	pthread_mutex_unlock(mutex);
}

void safely_set_int(pthread_mutex_t *mutex, int *value, int new)
{
	pthread_mutex_lock(mutex);
	*value = new;
	pthread_mutex_unlock(mutex);
}

void safely_set_time(pthread_mutex_t *mutex, time_t *value, time_t new)
{
	pthread_mutex_lock(mutex);
	*value = new;
	pthread_mutex_unlock(mutex);
}

void safely_add(pthread_mutex_t *mutex, int *value, int add)
{
	pthread_mutex_lock(mutex);
	*value += add;
	pthread_mutex_unlock(mutex);
}

void safe_print(t_philo *philo, const char *str, int id)
{
	pthread_mutex_lock(&philo->data->m_print);
	if (!safely_get_bool(&philo->data->m_data, &philo->data->is_dead))
		printf("%ld %d %s\n", get_time() - philo->data->start_time, id, str);
	pthread_mutex_unlock(&philo->data->m_print);
}