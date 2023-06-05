/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:24:43 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/05 22:19:04 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void    mutexes_initiator(t_philo *philo)
{
    int i;
    philo->params.philo_forks = malloc(sizeof(pthread_mutex_t) * philo->philo_info.nbr_of_philos);
    if (!philo->params.philo_forks)
    {
        exit_philo("couldn't malloc philosophers forks\n", &philo);
        return;
    }
    if (pthread_mutex_init(&philo->params.printf_mutex, NULL))
        exit_philo("couldnt initialize printf mutex\n", philo);
    if (pthread_mutex_init(&philo->params.read_philo_params, NULL))
        exit_philo("couldnt initilize read_philo_params mutex\n", philo);
    i = 0;
    while (i < philo->philo_info.nbr_of_philos)
    {
        if (pthread_mutex_init(&philo->params.philo_forks[i++], NULL))
        {
            exit_philo("couldn't initialize a philosophers fork mutex\n", philo);
            break;
        }
    }
    
}

void    thread_id_malloc(t_philo *philo)
{
    philo->params.threads_id = malloc(sizeof(pthread_t) * philo->philo_info.nbr_of_philos);
    if (!philo->params.threads_id)
        exit_philo("couldn't malloc enough threads ids", philo);
}
