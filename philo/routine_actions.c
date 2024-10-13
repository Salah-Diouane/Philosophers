/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:17:05 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/07 14:29:18 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking_fct(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

void	sleeping_fct(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep, philo);
}

void	eating_fct(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die, philo);
		print_message("died", philo, philo->id);
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo->dead_lock);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo, philo->id);
	print_message("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
