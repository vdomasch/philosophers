/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:22:47 by vdomasch          #+#    #+#             */
/*   Updated: 2024/06/24 12:35:53 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!str_is_digit(argv[i]))
		{
			printf("Error: argument %d is not a number\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}

bool	check_value(t_data *data)
{
	if (data->nb_philo < 1
		|| data->time_to_die < 1
		|| data->time_to_eat < 1
		|| data->time_to_sleep < 1
		|| data->nb_meal == 0)
	{
		printf("Error: arguments must be strictly positive\n");
		return (1);
	}
	return (0);
}
