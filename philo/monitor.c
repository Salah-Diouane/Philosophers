/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:16:36 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/08 08:02:13 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!check_if_is_die(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

int	is_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (((get_current_time() - philo->last_meal) >= time_to_die))
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (philos[0].num_of_philos > i)
	{
		if (is_dead(&philos[i], philos[i].time_to_die))
		{
			pthread_mutex_lock(philos[0].write_lock);
			if (!check_if_is_die(&philos[0]))
				printf("%zu %d died\n", get_current_time()
					- philos[0].start_time, philos[0].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			pthread_mutex_unlock(philos[0].write_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	is_finish_eating;

	i = 0;
	is_finish_eating = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (philos[0].num_of_philos > i)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].num_times_to_eat)
			is_finish_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (is_finish_eating == philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor_fuction(void *ph)
{
	t_philo	*philos;

	philos = (t_philo *)ph;
	while (1)
	{
		if (check_if_dead(philos) == 1)
			break ;
		if (check_if_all_ate(philos) == 1)
			break ;
	}
	return (ph);
}
