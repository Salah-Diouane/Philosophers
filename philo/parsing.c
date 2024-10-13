/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:10:15 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/08 09:26:06 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi( char *str)
{
	int		i;
	int		s;
	long	x;

	i = 0;
	s = 1;
	x = 0;
	if (!str[0])
		return (-1);
	while (str[i] == ' ')
		i++;
	if ((str[i] == '-' || str[i] == '+') && (str[i + 1]))
		s = 44 - str[i++];
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		if (((x * 10 + str[i] - '0') > 2147483647 && s == 1)
			|| ((x * 10 + str[i] - '0') > 2147483648 && s == -1))
			return (-1);
		x = x * 10 + str[i] - '0';
		i++;
	}
	return (x * s);
}

int	check_arg_content(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_args(char **argv)
{
	if (ft_atoi(argv[1]) > PHILO_MAX || ft_atoi(argv[1]) <= 0
		|| check_arg_content(argv[1]) == 1)
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (ft_atoi(argv[2]) <= 0 || check_arg_content(argv[2]) == 1)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(argv[3]) <= 0 || check_arg_content(argv[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(argv[4]) <= 0 || check_arg_content(argv[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_arg_content(argv[5]) == 1))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
	return (0);
}

void	print_instruction(void)
{
	printf("\t\t\t\t\t\t\tWRONG INPUT!\n\n\n");
	printf("[./philo] [nb_philos] [time_to_die]");
	printf(" [time_to_eat]  [time_to_sleep]");
	printf("[number_of_times_each_philosopher_must_eat ");
	printf("it's (optional argument)]\n\n");
	printf("Example:\n\n\n");
	printf("./philo 4 800 200 200 5.\n\n");
	printf("nb_philos: between 1 and 200.\n\n");
	printf("time_to_die: 60 or more.\n\n");
	printf("time_to_eat: 60 or more.\n\n");
	printf("time_to_sleep: 60 or more.\n\n");
	printf("number_of_times_each_philosopher_must_eat: ");
	printf("0 or more.\n\n");
}
