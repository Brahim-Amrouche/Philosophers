/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 19:04:12 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/17 22:53:13 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

int main(int argc, char *argv[])
{
    t_philo_bonus philo_bonus;
    int           status;
    int           i;

    memset(&philo_bonus, 0, sizeof(t_philo_bonus));
    parse_philo_bonus(argc, argv, &philo_bonus);
    philo_bonus_initiator(&philo_bonus);
    sem_wait(philo_bonus.bonus_params.syncro_sem);
    i = 0;
    philo_bonus.bonus_params.start_time = elapsed_time(0);
    while(i < philo_bonus.philo_info.nbr_of_philos)
    {
        philo_bonus.philo_info.philo_id = i + 1;
        philo_bonus.bonus_params.processes_ids[i] = fork();
        if (philo_bonus.bonus_params.processes_ids[i] == -1)
            exit_philo("couldnt fork\n");
        if (!philo_bonus.bonus_params.processes_ids[i])
            process_routine(&philo_bonus);
        i++;
    }
    sem_post(philo_bonus.bonus_params.syncro_sem);
    i = 0;
    while(waitpid(0, &status, 0) && philo_bonus.bonus_params.eat_count < philo_bonus.philo_info.nbr_of_philos)
    {
        if (status == 0)
            philo_bonus.bonus_params.eat_count++;
        else
            break;
    }
    i = 0;
    while (!status && i < philo_bonus.philo_info.nbr_of_philos)
    {
        if (!status)
            waitpid(philo_bonus.bonus_params.processes_ids[i++], NULL,  0);
        else
            kill(philo_bonus.bonus_params.processes_ids[i++], SIGKILL);
    }
    sem_close(philo_bonus.bonus_params.forks_sem);
    sem_close(philo_bonus.bonus_params.death_sem);
    return 0;
}