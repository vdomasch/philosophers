/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:49:28 by vincent           #+#    #+#             */
/*   Updated: 2024/06/24 15:50:17 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	observe_philo(t_data *data, int time_to_die)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo = &data->philo[i];
		if (safely_get_time(&philo->data->m_philo, &philo->last_meal)
			+ time_to_die < get_time())
		{
			safe_print(philo, "died", philo->id);
			safely_set_bool(&data->m_data, &data->is_dead, true);
			break ;
		}
		i++;
	}
}

static void	observer(t_data *data)
{
	int		nb_philo;
	int		time_to_die;
	int		refresh_time;

	nb_philo = safely_get_int(&data->m_data, &data->nb_philo);
	time_to_die = safely_get_int(&data->m_data, &data->time_to_die)
		+ (nb_philo / 10);
	refresh_time = time_to_die * 0.1;
	while (!safely_get_bool(&data->m_data, &data->is_dead))
	{
		observe_philo(data, time_to_die);
		if (safely_get_int(&data->m_data, &data->nb_full)
			== safely_get_int(&data->m_data, &data->nb_philo))
			safely_set_bool(&data->m_data, &data->is_dead, true);
		ft_usleep(refresh_time);
	}
}

static int	launch_thread(t_data *data)
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
	safely_set_time(&data->m_data, &data->start_time, get_time());
	safely_set_bool(&data->m_data, &data->is_ready, true);
	ft_usleep(10);
	observer(data);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->thread[i], NULL);
		i++;
	}
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
	if (check_value(&data))
	{
		free_destroy(&data, false);
		return (1);
	}
	init_philo(&data);
	launch_thread(&data);
	free_destroy(&data, true);
	return (0);
}
