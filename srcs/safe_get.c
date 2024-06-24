/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:41:20 by vdomasch          #+#    #+#             */
/*   Updated: 2024/06/24 12:41:27 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	safely_set_bool(pthread_mutex_t *mutex, bool *value, bool new)
{
	pthread_mutex_lock(mutex);
	*value = new;
	pthread_mutex_unlock(mutex);
}

void	safely_set_int(pthread_mutex_t *mutex, int *value, int new)
{
	pthread_mutex_lock(mutex);
	*value = new;
	pthread_mutex_unlock(mutex);
}

void	safely_set_time(pthread_mutex_t *mutex, time_t *value, time_t new)
{
	pthread_mutex_lock(mutex);
	*value = new;
	pthread_mutex_unlock(mutex);
}

void	safely_add(pthread_mutex_t *mutex, int *value, int add)
{
	pthread_mutex_lock(mutex);
	*value += add;
	pthread_mutex_unlock(mutex);
}
