/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:20:12 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/08 08:14:38 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_input(t_philo *philo, char **argv)
{
	philo->num_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->num_times_to_eat = ft_atoi(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

void	init_philos(t_philo *philos, t_global *p_global,
		pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		init_input(&philos[i], argv);
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].write_lock = &p_global->write_lock;
		philos[i].dead_lock = &p_global->dead_lock;
		philos[i].meal_lock = &p_global->meal_lock;
		philos[i].dead = &p_global->dead_flag;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].num_of_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_program(t_global *p_global, t_philo *philos)
{
	p_global->dead_flag = 0;
	p_global->philos = philos;
	pthread_mutex_init(&p_global->write_lock, NULL);
	pthread_mutex_init(&p_global->dead_lock, NULL);
	pthread_mutex_init(&p_global->meal_lock, NULL);
}

void	init_function(t_philo *philos, t_global *p_global,
		pthread_mutex_t *forks, char **argv)
{
	init_program(p_global, philos);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(philos, p_global, forks, argv);
	creat_threads_fct(p_global, forks);
}
