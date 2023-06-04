/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:57:50 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/04 18:48:10 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int main(int argc, char *argv[])
{
    t_philo philo;

    memset(&philo, 0, sizeof(philo));
    parse_philo(argc, argv, &philo);
    if (philo.parsing_error)
        return(1);
    philo.params.philo_mutexes = malloc(sizeof(pthread_mutex_t) * philo.nbr_of_philos);
    if (!philo.params.philo_mutexes)
    {
        exit_philo("couldn't malloc mutexes\n", &philo);
        return (1);
    }
    philo.params.start_timer = elapsed_time(0);

}