/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:57:50 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/09 23:48:59 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int main(int argc, char *argv[])
{
    t_philo philo;
    t_thread_data *data;
    int     i;

    memset(&philo, 0, sizeof(t_philo));
    parse_philo(argc, argv, &philo);
    if (philo.parsing_error)
        return(1);
    mutexes_initiator(&philo);
    if (philo.parsing_error)
        return (1);
    philo.params.start_timer = elapsed_time(0);
    i = 0;
    while (i < philo.philo_info.nbr_of_philos)
    {
        data = malloc(sizeof(t_thread_data));
        data->i = i++;
        data->philo = &philo;
        if(pthread_create(&philo.params.thread_id, NULL, philo_routine, (void *) data))
        {
            exit_philo("couldn't create threads\n",&philo);
            return (1);
        }
        pthread_detach(philo.params.thread_id);
    }
    while (!philo.params.death)
        ;
    return (0);
}