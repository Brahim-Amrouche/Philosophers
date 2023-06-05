/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:49:25 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/05 22:31:41 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void    philo_routine(t_philo *philo)
{
    t_philo_instance philosopher;

    pthread_mutex_lock(&philo->params.read_philo_params);
    philosopher = philo->philo_info;
    philosopher.nbr_of_philos = philo->params.philosopher_id;
    pthread_mutex_unlock(&philo->params.read_philo_params);
    pthread_mutex_lock(&philo->params.printf_mutex);
    printf("hello philosophers numbro %d\n", philosopher.nbr_of_philos);
    pthread_mutex_unlock(&philo->params.printf_mutex);
}

