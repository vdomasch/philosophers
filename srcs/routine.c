/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:33:03 by vdomasch          #+#    #+#             */
/*   Updated: 2024/06/24 13:38:33 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks(t_philo *philo, pthread_mutex_t *fork1,
					pthread_mutex_t *fork2)
{
	pthread_mutex_lock(fork1);
	safe_print(philo, "has taken a fork", philo->id);
	pthread_mutex_lock(fork2);
	safe_print(philo, "has taken a fork", philo->id);
}

void	eat_meal(t_philo *philo)
{
	safe_print(philo, "is eating", philo->id);
	safely_set_time(&philo->data->m_philo, &philo->last_meal, get_time());
	safely_add(&philo->data->m_philo, &philo->nb_meal, 1);
	ft_usleep(philo->data->time_to_eat);
	if (philo->nb_meal == safely_get_int(&philo->data->m_data,
			&philo->data->nb_meal))
	{
		philo->is_full = true;
		safely_add(&philo->data->m_data, &philo->data->nb_full, 1);
	}
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	even_routine(t_philo *philo)
{
	while (!safely_get_bool(&philo->data->m_data, &philo->data->is_dead))
	{
		pthread_mutex_lock(&philo->left_fork);
		safe_print(philo, "has taken a fork", philo->id);
		pthread_mutex_lock(philo->right_fork);
		safe_print(philo, "has taken a fork", philo->id);
		//take_forks(philo, &philo->left_fork, philo->right_fork);
		safe_print(philo, "is eating", philo->id);
		safely_set_time(&philo->data->m_philo, &philo->last_meal, get_time());
		safely_add(&philo->data->m_philo, &philo->nb_meal, 1);
		ft_usleep(philo->data->time_to_eat);
		if (philo->nb_meal == safely_get_int(&philo->data->m_data,
				&philo->data->nb_meal))
		{
			philo->is_full = true;
			safely_add(&philo->data->m_data, &philo->data->nb_full, 1);
		}
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		//eat_meal(philo);
		safe_print(philo, "is sleeping", philo->id);
		ft_usleep(philo->data->time_to_sleep);
		safe_print(philo, "is thinking", philo->id);
	}
}

void	odd_routine(t_philo *philo)
{
	while (!safely_get_bool(&philo->data->m_data, &philo->data->is_dead))
	{
		pthread_mutex_lock(philo->right_fork);
		safe_print(philo, "has taken a fork", philo->id);
		pthread_mutex_lock(&philo->left_fork);
		safe_print(philo, "has taken a fork", philo->id);
		//take_forks(philo, philo->right_fork, &philo->left_fork);
		safe_print(philo, "is eating", philo->id);
		safely_set_time(&philo->data->m_philo, &philo->last_meal, get_time());
		safely_add(&philo->data->m_philo, &philo->nb_meal, 1);
		ft_usleep(philo->data->time_to_eat);
		if (philo->nb_meal == safely_get_int(&philo->data->m_data,
				&philo->data->nb_meal))
		{
			philo->is_full = true;
			safely_add(&philo->data->m_data, &philo->data->nb_full, 1);
		}
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		//eat_meal(philo);
		safe_print(philo, "is sleeping", philo->id);
		ft_usleep(philo->data->time_to_sleep);
		safe_print(philo, "is thinking", philo->id);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
	time_t	start_time;

	philo = (t_philo *)arg;
	start_time = safely_get_time(&philo->data->m_data,
			&philo->data->start_time);
	safely_add(&philo->data->m_data, &philo->data->nb_ready, 1);
	while (!safely_get_bool(&philo->data->m_data, &philo->data->is_ready))
		ft_usleep(10);
	safely_set_time(&philo->data->m_philo, &philo->last_meal, start_time);
	if (philo->id % 2)
		even_routine(philo);
	else
	{
		safe_print(philo, "is thinking", philo->id);
		ft_usleep(100);
		odd_routine(philo);
	}
	return (NULL);
}
