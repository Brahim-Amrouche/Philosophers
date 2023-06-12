/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:49:25 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/12 20:20:08 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static  void    printf_philo_state(t_philo *philo, t_philo_instance *philosopher)
{
    // pthread_mutex_lock(&philo->params.printf_mutex);
    pthread_mutex_lock(&philo->params.death_mutex);
    if (philo->params.death)
    {
        pthread_mutex_unlock(&philo->params.death_mutex);
        // pthread_mutex_unlock(&philo->params.printf_mutex);
        return;
    }
    pthread_mutex_unlock(&philo->params.death_mutex);
    if (philosopher->state == FORK_TAKEN)
        printf("%ld %d has taken a fork\n", elapsed_time(philo->params.start_timer), philosopher->nbr_of_philos);
    else if (philosopher->state == EATING)
        printf("%ld %d is eating\n", elapsed_time(philo->params.start_timer), philosopher->nbr_of_philos);
    else if (philosopher->state == SLEEPING)
        printf("%ld %d is sleeping\n", elapsed_time(philo->params.start_timer), philosopher->nbr_of_philos);
    else if (philosopher->state == THINKING)
        printf("%ld %d is thinking\n", elapsed_time(philo->params.start_timer), philosopher->nbr_of_philos);
    else if (philosopher->state == DIED)
        printf("%ld %d died\n", elapsed_time(philo->params.start_timer), philosopher->nbr_of_philos);
    // pthread_mutex_unlock(&philo->params.printf_mutex);
}

static  t_boolean take_forks(t_philo *philo, t_philo_instance *philosopher)
{
    pthread_mutex_lock(&philo->params.philo_forks[philosopher->nbr_of_philos - 1]);
    if (philosopher->wake_time && 
        elapsed_time(philo->params.start_timer) - philosopher->wake_time >= philosopher->time_to_die)
    {
        philosopher->state = DIED;
        printf_philo_state(philo, philosopher);
        pthread_mutex_lock(&philo->params.death_mutex);
        philo->params.death = TRUE;
        pthread_mutex_unlock(&philo->params.death_mutex);
        pthread_mutex_unlock(&philo->params.philo_forks[philosopher->nbr_of_philos - 1]);
        return FALSE;
    }
    philosopher->state = FORK_TAKEN;
    printf_philo_state(philo, philosopher);
    pthread_mutex_lock(&philo->params.philo_forks[philosopher->nbr_of_philos % philo->philo_info.nbr_of_philos]);
    printf_philo_state(philo, philosopher);
    return TRUE;
}

static void eat(t_philo *philo, t_philo_instance *philosopher)
{
    philosopher->state = EATING;
    printf_philo_state(philo, philosopher);
    msleep(philosopher->time_to_eat); 
    pthread_mutex_unlock(&philo->params.philo_forks[philosopher->nbr_of_philos - 1]);
    pthread_mutex_unlock(&philo->params.philo_forks[philosopher->nbr_of_philos % philo->philo_info.nbr_of_philos]);
}

static void go_sleep(t_philo *philo, t_philo_instance *philosopher)
{
    philosopher->state = SLEEPING;
    printf_philo_state(philo, philosopher);
    msleep(philosopher->time_to_sleep);
}

static void think(t_philo *philo, t_philo_instance *philosopher)
{
    philosopher->state = THINKING;
    printf_philo_state(philo, philosopher);
    philosopher->wake_time = elapsed_time(philo->params.start_timer);
}

void    philo_routine(t_thread_data *data)
{
    t_philo_instance philosopher;
    t_philo *philo;
    t_boolean   meal_count;

    philo = data->philo;
    memset(&philosopher, 0, sizeof(t_philo_instance));
    philosopher = philo->philo_info;
    philosopher.nbr_of_philos = data->i + 1;
    free(data);
    meal_count = FALSE;
    if (philosopher.nbr_of_eats)
        meal_count = TRUE;
    if (!(philosopher.nbr_of_philos % 2))
        msleep(1);
    while (!meal_count || philosopher.nbr_of_eats)
    {   
        if(philo->params.death || !take_forks(philo, &philosopher))
            break;
        eat(philo, &philosopher);
        go_sleep(philo, &philosopher);
        think(philo, &philosopher);
        philosopher.nbr_of_eats--;
    }
}

