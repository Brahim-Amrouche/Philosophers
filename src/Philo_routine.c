/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:49:25 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/06 21:17:55 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static  void    printf_philo_state(t_philo *philo, t_philo_instance *philosopher)
{
    pthread_mutex_lock(&philo->params.printf_mutex);
    if (philosopher->state == FORK_TAKEN)
        printf("%d has taken a fork\n", philosopher->nbr_of_philos);
    else if (philosopher->state == EATING)
        printf("%d is eating\n", philosopher->nbr_of_philos);
    else if (philosopher->state == SLEEPING)
        printf("%d is sleeping\n", philosopher->nbr_of_philos);
    else if (philosopher->state == THINKING)
        printf("%d is thinking\n", philosopher->nbr_of_philos);
    pthread_mutex_unlock(&philo->params.printf_mutex);

}

void    msleep(time_t delay)
{
    time_t n;

    n = delay * 10;
    while (n--)
        usleep(100);
}

void    philo_routine(t_philo *philo)
{
    t_philo_instance philosopher;

    pthread_mutex_lock(&philo->params.read_philo_params);
    philosopher = philo->philo_info;
    philosopher.nbr_of_philos = philo->params.philosopher_id + 1;
    pthread_mutex_unlock(&philo->params.read_philo_params);
    // printf("%d own mutex address in thread %p\n", philosopher.nbr_of_philos, &philo->params.philo_forks[philosopher.nbr_of_philos - 1]);
    // printf("%d second mutex in thread %p\n", philosopher.nbr_of_philos, &philo->params.philo_forks[philosopher.nbr_of_philos % philo->philo_info.nbr_of_philos]);
    while (TRUE)
    {
        printf("hello %d\n", philosopher.nbr_of_philos);
        if (pthread_mutex_lock(&philo->params.philo_forks[philosopher.nbr_of_philos - 1]))
            printf("hello error \n");
        philosopher.state = FORK_TAKEN;
        printf_philo_state(philo, &philosopher);
        if (pthread_mutex_lock(&philo->params.philo_forks[philosopher.nbr_of_philos % philo->philo_info.nbr_of_philos]))
            printf("error from the second \n");
        printf_philo_state(philo, &philosopher);
        msleep(philosopher.time_to_eat); 
        pthread_mutex_unlock(&philo->params.philo_forks[philosopher.nbr_of_philos - 1]);
        pthread_mutex_unlock(&philo->params.philo_forks[philosopher.nbr_of_philos % philo->philo_info.nbr_of_philos]);
        // philosopher.state = SLEEPING;
        // printf_philo_state(philo, &philosopher);
        // msleep(philosopher.time_to_sleep);
        // sleep(2);
        break;
    }
    


}

