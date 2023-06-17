/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:38:19 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/17 22:09:13 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

void    philo_bonus_initiator(t_philo_bonus *philo_bonus)
{
    sem_unlink("/forks_count");
    philo_bonus->bonus_params.forks_sem = sem_open("/forks_count", O_CREAT, 0644, philo_bonus->philo_info.nbr_of_philos);
    if (philo_bonus->bonus_params.forks_sem == SEM_FAILED)
        exit_philo("couldnt create the forks semaphore\n");
    sem_unlink("/death_sem");
    philo_bonus->bonus_params.death_sem = sem_open("/death_sem", O_CREAT, 0644, 1);
    if (philo_bonus->bonus_params.death_sem == SEM_FAILED)
        exit_philo("couldnt create the death semaphore\n");
    sem_unlink("/eat_sem");
    philo_bonus->bonus_params.eat_time_sem = sem_open("/eat_sem", O_CREAT, 0644, 1);
    if (philo_bonus->bonus_params.eat_time_sem == SEM_FAILED)
        exit_philo("couldnt create the eat_time semaphore\n");
    sem_unlink("/start_sem");
    philo_bonus->bonus_params.syncro_sem = sem_open("/start_sem", O_CREAT, 0644, 1);
    if (philo_bonus->bonus_params.syncro_sem == SEM_FAILED)
        exit_philo("couldnt create the syncro semaphore\n");
    philo_bonus->bonus_params.processes_ids = malloc(sizeof(pid_t) * philo_bonus->philo_info.nbr_of_philos);
    if (!philo_bonus->bonus_params.processes_ids)
        exit_philo("couldn't malloc process_ids \n");
}

