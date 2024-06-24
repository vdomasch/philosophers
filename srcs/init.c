/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:52:44 by vdomasch          #+#    #+#             */
/*   Updated: 2024/06/24 15:35:09 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	error_malloc(void *ptr)
{
	if (!ptr)
	{
		printf("Error: malloc failed\n");
		return (true);
	}
	return (false);
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].nb_meal = 0;
		data->philo[i].is_full = false;
		data->philo[i].last_meal = get_time();
		data->philo[i].data = data;
		pthread_mutex_init(&data->philo[i].left_fork, NULL);
		if (i < data->nb_philo - 1)
		{
			data->philo[i].neighbor_fork = &data->philo[i + 1].fork;
			data->philo[i].right_fork = &data->philo[i + 1].left_fork;
		}
		else
		{
			data->philo[i].neighbor_fork = &data->philo[0].fork;
			data->philo[i].right_fork = &data->philo[0].left_fork;
		}
		i++;
	}
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nb_meal = -1;
	if (argc == 6)
		data->nb_meal = ft_atoi(argv[5]);
	data->nb_full = 0;
	data->is_dead = false;
	data->is_ready = false;
	data->start_time = get_time();
	data->thread = malloc(sizeof(pthread_t) * data->nb_philo);
	if (error_malloc(data->thread))
		return (1);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (error_malloc(data->philo))
	{
		free(data->thread);
		return (1);
	}
	pthread_mutex_init(&data->m_philo, NULL);
	pthread_mutex_init(&data->m_print, NULL);
	pthread_mutex_init(&data->m_ready, NULL);
	pthread_mutex_init(&data->m_data, NULL);
	return (0);
}
