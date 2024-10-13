/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:03:40 by sdiouane          #+#    #+#             */
/*   Updated: 2024/07/08 09:25:19 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct philo_strcut
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct struct_global
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_global;

// Main
int					check_arg_content(char *arg);
int					check_valid_args(char **argv);
void				destory_all(t_global *p_global,
						pthread_mutex_t *forks);					
// Initialization
void				init_function(t_philo *philos, t_global *p_global,
						pthread_mutex_t *forks, char **argv);
void				init_program(t_global *p_global, t_philo *philos);
void				init_forks(pthread_mutex_t *forks, int philo_num);
void				init_philos(t_philo *philos, t_global *p_global,
						pthread_mutex_t *forks, char **argv);
void				init_input(t_philo *philo, char **argv);

// Threads
int					creat_threads_fct(t_global *p_global,
						pthread_mutex_t *forks);
void				*monitor_fuction(void *ph);
void				*philo_routine(void *ph);

// Actions
void				eating_fct(t_philo *philo);
void				sleeping_fct(t_philo *philo);
void				thinking_fct(t_philo *philo);

// Monitor utils
int					check_if_is_die(t_philo *philo);
int					check_if_all_ate(t_philo *philos);
int					check_if_dead(t_philo *philos);
int					is_dead(t_philo *philo, size_t time_to_die);

// Utils
int					ft_usleep(size_t milliseconds, t_philo *ph);
int					ft_strlen(char *str);
void				print_message(char *str, t_philo *philo, int id);
size_t				get_current_time(void);

//Parsing
void				print_instruction(void);
int					ft_atoi(char *str);
int					check_arg_content(char *arg);
int					check_valid_args(char **argv);
void				print_instruction(void);

#endif