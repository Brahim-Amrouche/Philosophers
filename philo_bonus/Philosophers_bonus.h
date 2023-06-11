/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:52:50 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/12 00:04:45 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
#define PHILOSOPHERS_BONUS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <semaphore.h>
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
    int nbr_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nbr_of_eats;
    t_philo_states  state;
    time_t          wake_time;
}   t_philo_instance;

typedef struct s_philo_bonus_params
{
    time_t           start_time;
    sem_t            *forks_sem;
    pid_t            *processes_ids;
}   t_philo_bonus_params;

typedef struct s_philo_bonus
{
    t_philo_instance        philo_info;
    t_philo_bonus_params    bonus_params;
}   t_philo_bonus;

// exit_bonus_philo.c
void    exit_philo(char *message);
// int_parser.c
void	parse_philo_bonus(int argc, char *argv[], t_philo_bonus *philo);
// initiators.c
void    philo_bonus_initiator(t_philo_bonus *philo_bonus);

// helpers
// ft_strlen.c
size_t	ft_strlen(const char *s);
// ft_atoi.c
t_boolean   ft_isdigit(int c);
long        ft_atoi(const char *str);


#endif