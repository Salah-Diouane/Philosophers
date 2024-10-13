/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:16:19 by sdiouane          #+#    #+#             */
/*   Updated: 2024/06/12 22:18:09 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_global		p_global;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (argc != 5 && argc != 6)
		return (print_instruction(), 0);
	if (check_valid_args(argv) == 1)
		return (1);
	init_function(philos, &p_global, forks, argv);
	destory_all(&p_global, forks);
	return (0);
}
