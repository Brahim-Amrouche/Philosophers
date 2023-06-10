/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:57:50 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/10 13:54:45 by bamrouch         ###   ########.fr       */
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
    thread_id_malloc(&philo);
    if (philo.parsing_error)
        return (1);
    philo.params.start_timer = elapsed_time(0);
    i = 0;
    while (i < philo.philo_info.nbr_of_philos)
    {
        data = malloc(sizeof(t_thread_data));
        data->i = i;
        data->philo = &philo;
        if(pthread_create(&philo.params.threads_id[i], NULL, philo_routine, (void *) data))
        {
            exit_philo("couldn't create threads\n",&philo);
            return (1);
        }
        i++;
    }
    i = 0;
    while (i < philo.philo_info.nbr_of_philos)
        pthread_join(philo.params.threads_id[i++], NULL);
    return (0);
}