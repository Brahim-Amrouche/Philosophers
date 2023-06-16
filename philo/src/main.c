/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:57:50 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/16 22:40:53 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static  void set_philo_info(t_philo *philo, int i)
{
    memset(&philo->params.philos_data[i], 0, sizeof(t_philo_instance));
    philo->params.philos_data[i] = philo->philo_info;
    philo->params.philos_data[i].philo_id = i + 1;
    philo->params.philos_data[i].own_mutex = &philo->params.philo_forks[i];
    philo->params.philos_data[i].other_mutex = &philo->params.philo_forks[(i + 1) % (philo->philo_info.philo_id)];
    philo->params.philos_data[i].philo = philo;
    if (pthread_mutex_init(&philo->params.philos_data[i].wake_mutex, NULL))
        exit_philo("couldn't init wake mutex\n", philo);
}

int main(int argc, char *argv[])
{
    t_philo philo;
    int     i;

    memset(&philo, 0, sizeof(t_philo));
    parse_philo(argc, argv, &philo);
    if (philo.parsing_error)
        return(1);
    mutexes_initiator(&philo);
    if (philo.parsing_error)
        return (1);
    pthread_mutex_lock(&philo.params.start_mutex);
    i = 0;
    while (i < philo.philo_info.philo_id)
    {
        set_philo_info(&philo, i);
        if (philo.parsing_error)
            return (1);
        if(pthread_create(&philo.params.threads_id[i], NULL, philo_routine, &philo.params.philos_data[i]))
        {
            exit_philo("couldn't create threads\n",&philo);
            return (1);
        }
        i++;
    }
    philo.params.start_timer = elapsed_time(0);
    pthread_mutex_unlock(&philo.params.start_mutex);
    while (TRUE && !philo.death && philo.params.died_count < philo.philo_info.philo_id)
    {
        i = 0;
        while (i < philo.philo_info.philo_id)
        {
            pthread_mutex_lock(&philo.params.philos_data[i].wake_mutex);
            if (philo.params.philos_data[i].die)
                philo.params.died_count++;
            else if (elapsed_time(philo.params.start_timer) - philo.params.philos_data[i].wake_time >= philo.philo_info.time_to_die)
            {
                pthread_mutex_lock(&philo.params.death_mutex);
                philo.death = TRUE;
                pthread_mutex_unlock(&philo.params.death_mutex);
            }
            pthread_mutex_unlock(&philo.params.philos_data[i].wake_mutex);
            i++;
        }
    }
    i = 0;
    while (i < philo.philo_info.philo_id)
        pthread_join(philo.params.threads_id[i++], NULL);
    printf("ended here damn\n");
    philo_mem_cleaner(&philo);
    return (0);
}