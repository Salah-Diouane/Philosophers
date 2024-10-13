/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:17:22 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/07 22:43:24 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_is_die(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->id % 2 == 0)
		ft_usleep(20, philo);
	while (!check_if_is_die(philo))
	{
		eating_fct(philo);
		sleeping_fct(philo);
		thinking_fct(philo);
	}
	return (ph);
}

int	creat_threads_fct(t_global *p_global, pthread_mutex_t *forks)
{
	pthread_t	monitor;
	int			i;

	if (pthread_create(&monitor, NULL, &monitor_fuction, p_global->philos) != 0)
		destory_all(p_global, forks);
	i = 0;
	while (i < p_global->philos[0].num_of_philos)
	{
		if (pthread_create(&p_global->philos[i].thread, NULL, &philo_routine,
				&p_global->philos[i]) != 0)
			destory_all(p_global, forks);
		i++;
	}
	i = 0;
	if (pthread_join(monitor, NULL) != 0)
		destory_all(p_global, forks);
	while (i < p_global->philos[0].num_of_philos)
	{
		if (pthread_join(p_global->philos[i].thread, NULL) != 0)
			destory_all(p_global, forks);
		i++;
	}
	return (0);
}
