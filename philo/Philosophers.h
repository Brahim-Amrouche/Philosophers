/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:37:15 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/16 22:20:52 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <limits.h>

typedef enum e_boolean
{
    FALSE,
    TRUE
}   t_boolean;

typedef enum e_philo_states
{    
    FORK_TAKEN,
    EATING,
    SLEEPING,
    THINKING,
    DIED    
}   t_philo_states;

typedef struct philo_instance
{
    int	philo_id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nbr_of_eats;
    t_philo_states  state;
	pthread_mutex_t	wake_mutex;
	pthread_mutex_t *own_mutex;
	pthread_mutex_t *other_mutex;
	void			*philo;
    time_t          wake_time;
    t_boolean       die;
}   t_philo_instance;

typedef struct s_philo_params
{
    time_t          	start_timer;
    pthread_mutex_t		*philo_forks;
    pthread_t			*threads_id;
    t_philo_instance	*philos_data;
    pthread_mutex_t		printf_mutex;
	pthread_mutex_t		start_mutex;
	pthread_mutex_t		death_mutex;
    int                 died_count;
}   t_philo_params;

typedef struct s_philo
{
    t_philo_instance	philo_info;
    t_boolean			parsing_error;
    t_philo_params		params;
    t_boolean           death;
}   t_philo;

// initiators.c
void    mutexes_initiator(t_philo *philo);
void    thread_id_malloc(t_philo *philo);
//int_parser.c
void	parse_philo(int argc, char *argv[], t_philo *philo);
//time.c
void    msleep(time_t delay);
time_t  elapsed_time(time_t start);
// Philo_routine.c
void    philo_routine(t_philo_instance *data);
// cleaner.c
void    philo_mem_cleaner(t_philo *philo);


// helpers
// ft_strlen.c
size_t	ft_strlen(const char *s);
// ft_atoi.c
t_boolean   ft_isdigit(int c);
long        ft_atoi(const char *str);

//exit_philo.c
void    exit_philo(char *message, t_philo *philo);

#endif