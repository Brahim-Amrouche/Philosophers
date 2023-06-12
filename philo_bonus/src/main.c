/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 19:04:12 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/12 20:01:46 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

// void    process_worker_thread(t_philo_bonus *philo_bonus)
// {
//     pthread_t thread_id;

//     pthread_create(&thread_id, NULL, process_routine, philo_bonus);
//     pthread_join(thread_id, NULL);

// }

int main(int argc, char *argv[])
{
    t_philo_bonus philo_bonus;
    int           i;
    int           status;

    memset(&philo_bonus, 0, sizeof(t_philo_bonus));
    parse_philo_bonus(argc, argv, &philo_bonus);
    philo_bonus_initiator(&philo_bonus);
    philo_bonus.bonus_params.start_time = elapsed_time(0);
    i = 0;
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
    i = 0;
    while (i < philo_bonus.philo_info.nbr_of_philos)
    {
        waitpid(philo_bonus.bonus_params.processes_ids[i], &status, NULL);
        i++;
    }
    sem_close(philo_bonus.bonus_params.forks_sem);
    sem_unlink("/forks_count");
    return 0;
}