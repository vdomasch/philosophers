/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 14:52:09 by vdomasch          #+#    #+#             */
/*   Updated: 2024/06/24 13:28:41 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>
# include <errno.h>

# define NBP "1. Number of philosophers\n"
# define TTD "2. Time to die\n"
# define TTE "3. Time to eat\n"
# define TTS "4. Time to sleep\n"
# define NBM "5. Number of meals (optional)\n"

typedef struct s_philo
{
	int				id;
	int				nb_meal;
	bool			fork;
	bool			is_full;
	time_t			last_meal;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal;
	int				nb_full;
	int				nb_ready;
	bool			is_dead;
	bool			is_ready;
	time_t			start_time;
	pthread_t		*thread;
	pthread_mutex_t	m_philo;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_ready;
	pthread_mutex_t	m_data;
	t_philo			*philo;
}	t_data;

size_t	ft_strlen(const char *s);
int		str_is_digit(const char *str);
int		ft_atoi(const char *str);
void	ft_usleep(time_t time);
time_t	get_time(void);

bool	check_args(int argc, char **argv);
bool	check_value(t_data *data);

int		init_data(t_data *data, int argc, char **argv);
void	init_philo(t_data *data);

void	*routine(void *arg);
void	observer(t_data *data);
int		launch_thread(t_data *data);

bool	safely_get_bool(pthread_mutex_t *mutex, bool *var);
int		safely_get_int(pthread_mutex_t *mutex, int *var);
time_t	safely_get_time(pthread_mutex_t *mutex, time_t *var);
void	safely_set_bool(pthread_mutex_t *mutex, bool *var, bool value);
void	safely_set_int(pthread_mutex_t *mutex, int *var, int value);
void	safely_set_time(pthread_mutex_t *mutex, time_t *var, time_t value);
void	safely_add(pthread_mutex_t *mutex, int *var, int value);
void	safe_print(t_philo *philo, const char *str, int id);

#endif
