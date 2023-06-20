/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:52:50 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/20 16:09:50 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_boolean
{
	FALSE,
	TRUE
}							t_boolean;

typedef enum e_philo_states
{
	FORK_TAKEN,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}							t_philo_states;

typedef struct philo_instance
{
	int						nbr_of_philos;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						nbr_of_eats;
	int						philo_id;
	t_philo_states			state;
	struct timeval			wake_time;
	t_boolean				count_meals;
}							t_philo_instance;

typedef struct s_philo_bonus_params
{
	time_t					start_time;
	sem_t					*forks_sem;
	sem_t					*death_sem;
	sem_t					*eat_time_sem;
	sem_t					*syncro_sem;
	pid_t					*processes_ids;
	int						eat_count;
}							t_philo_bonus_params;

typedef struct s_philo_bonus
{
	t_philo_instance		philo_info;
	t_philo_bonus_params	bonus_params;
}							t_philo_bonus;

// process_routine.c
void						process_routine(t_philo_bonus *philo_bonus);

// process_routine_helper.c
void						print_philo_state(t_philo_bonus *philo_bonus);
void						process_supervisor(t_philo_bonus *philo_bonus);
// exit_bonus_philo.c
void						exit_philo(char *message);
// int_parser.c
void						parse_philo_bonus(int argc, char *argv[],
								t_philo_bonus *philo);
// initiators.c
void						philo_bonus_initiator(t_philo_bonus *philo_bonus);
//time.c
void						msleep(time_t delay);
time_t						elapsed_time(time_t start);

// helpers
// ft_strlen.c
size_t						ft_strlen(const char *s);
// ft_atoi.c
t_boolean					ft_isdigit(int c);
long						ft_atoi(const char *str);

#endif