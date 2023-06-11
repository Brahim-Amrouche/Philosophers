/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 19:04:12 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/12 00:06:07 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"


int main(int argc, char *argv[])
{
    t_philo_bonus philo_bonus;

    memset(&philo_bonus, 0, sizeof(t_philo_bonus));
    parse_philo_bonus(argc, argv, &philo_bonus);
    philo_bonus_initiator(&philo_bonus);
    printf("hello \n");
    sem_close(philo_bonus.bonus_params.forks_sem);
    sem_unlink("/forks_count");
    return 0;
}