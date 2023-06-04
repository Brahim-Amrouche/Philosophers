/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:37:15 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/04 18:19:45 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"
#include "string.h"
#include "sys/types.h"
#include "sys/time.h"
#include "limits.h"

typedef enum e_boolean
{
    FALSE,
    TRUE
}   t_boolean;

typedef struct s_philo_params
{
    time_t          start_timer;
    pthread_mutex_t	*philo_mutexes;
    pthread_mutex_t	printf_mutex;

}   t_philo_params;

typedef struct s_philo
{
    int nbr_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nbr_of_eats;
    t_boolean   parsing_error;
    t_philo_params params;
}   t_philo;

//int_parser.c
void	parse_philo(int argc, char *argv[], t_philo *philo);
//time.c
time_t  elapsed_time(time_t start);



// helpers
// ft_strlen.c
size_t	ft_strlen(const char *s);
// ft_atoi.c
t_boolean   ft_isdigit(int c);
long        ft_atoi(const char *str);


//exit_philo.c
void    exit_philo(char *message, t_philo *philo);

#endif