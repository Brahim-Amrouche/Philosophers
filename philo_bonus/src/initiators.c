/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:38:19 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/12 00:04:21 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

void    philo_bonus_initiator(t_philo_bonus *philo_bonus)
{
    philo_bonus->bonus_params.forks_sem = sem_open("/forks_count", O_CREAT, 0644, philo_bonus->philo_info.nbr_of_philos);
    if (philo_bonus->bonus_params.forks_sem == SEM_FAILED)
        exit_philo("couldnt create the semaphore\n");
    philo_bonus->bonus_params.processes_ids = malloc(sizeof(pid_t) * philo_bonus->philo_info.nbr_of_philos);
    if (!philo_bonus->bonus_params.processes_ids)
        exit_philo("couldn't malloc process_ids \n");
}

