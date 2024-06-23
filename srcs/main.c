/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:49:28 by vincent           #+#    #+#             */
/*   Updated: 2024/06/23 12:58:21 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks(t_philo *philo, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
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
	usleep(philo->data->time_to_eat * 1000);
	if (philo->nb_meal == safely_get_int(&philo->data->m_data, &philo->data->nb_meal))
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
		take_forks(philo, &philo->left_fork, philo->right_fork);
		eat_meal(philo);
		safe_print(philo, "is sleeping", philo->id);
		usleep(philo->data->time_to_sleep * 1000);
		safe_print(philo, "is thinking", philo->id);
	}
	
}

void	odd_routine(t_philo *philo)
{
	while (!safely_get_bool(&philo->data->m_data, &philo->data->is_dead))
	{
		take_forks(philo, philo->right_fork, &philo->left_fork);
		eat_meal(philo);
		safe_print(philo, "is sleeping", philo->id);
		usleep(philo->data->time_to_sleep * 1000);
		safe_print(philo, "is thinking", philo->id);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
	size_t	start_time;
	
	philo = (t_philo *)arg;
	safely_add(&philo->data->m_data, &philo->data->nb_ready, 1);
	while (!safely_get_bool(&philo->data->m_data, &philo->data->is_ready))
		usleep(1000);
	start_time = safely_get_time(&philo->data->m_data, &philo->data->start_time);
	safely_set_time(&philo->data->m_philo, &philo->last_meal, start_time);
	if (philo->id % 2)
	{
		even_routine(philo);
	}
	else
	{
		safe_print(philo, "is thinking", philo->id);
		usleep(10000);
		odd_routine(philo);
	}
	return (NULL);
}

void	observer(t_data *data)
{
	t_philo	*philo;
	int time_to_die;
	int	i;
	
	time_to_die = safely_get_int(&data->m_data, &data->time_to_die);
	//while (safely_get_int(&data->m_data, &data->nb_ready)
	//		!= safely_get_int(&data->m_data, &data->nb_philo))
	//	usleep(500);
	while (!safely_get_bool(&data->m_data, &data->is_dead))
	{
		i = 0;
		while (i < data->nb_philo)
		{
			philo = &data->philo[i];
			if (safely_get_time(&philo->data->m_philo, &philo->last_meal) + time_to_die < get_time())
			{
				safe_print(philo, "died", philo->id);
				safely_set_bool(&data->m_data, &data->is_dead, true);
				break ;
			}
			i++;
		}
		if (safely_get_int(&data->m_data, &data->nb_full) == safely_get_int(&data->m_data, &data->nb_philo))
			safely_set_bool(&data->m_data, &data->is_dead, true);
		usleep(500000);
	}
}

int	launch_thread(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->thread[i], NULL, &routine, &data->philo[i]))
		{
			printf("Error: pthread_create failed\n");
			return (1);
		}
		i++;
	}
	safely_set_bool(&data->m_data, &data->is_ready, true);
	usleep(1000);
	observer(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments:\n"NBP TTD TTE TTS NBM);
		return (1);
	}
	if (check_args(argc, argv))
		return (1);
	if (init_data(&data, argc, argv))
		return (1);
	init_philo(&data);
	launch_thread(&data);
	free(data.thread);
	free(data.philo);
	return (0);
}