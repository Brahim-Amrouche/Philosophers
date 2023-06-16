/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:49:25 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/16 22:49:45 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static  void    printf_philo_state(t_philo *philo, t_philo_instance *philosopher)
{
    pthread_mutex_lock(&philo->params.printf_mutex);
    pthread_mutex_lock(&philo->params.death_mutex);
    printf("data die %d\n", philosopher->die);
    if(philosopher->die || philo->death)
    {
        pthread_mutex_unlock(&philo->params.printf_mutex);
        pthread_mutex_unlock(&philo->params.death_mutex);
        philosopher->die = TRUE;
        return;
    }
    pthread_mutex_unlock(&philo->params.death_mutex);
    if (philosopher->state == FORK_TAKEN)
        printf("%ld %d has taken a fork\n", elapsed_time(philo->params.start_timer), philosopher->philo_id);
    else if (philosopher->state == EATING)
        printf("%ld %d is eating\n", elapsed_time(philo->params.start_timer), philosopher->philo_id);
    else if (philosopher->state == SLEEPING)
        printf("%ld %d is sleeping\n", elapsed_time(philo->params.start_timer), philosopher->philo_id);
    else if (philosopher->state == THINKING)
        printf("%ld %d is thinking\n", elapsed_time(philo->params.start_timer), philosopher->philo_id);
    else if (philosopher->state == DIED)
        printf("%ld %d died\n", elapsed_time(philo->params.start_timer), philosopher->philo_id);
    pthread_mutex_unlock(&philo->params.printf_mutex);
}

static  t_boolean take_forks(t_philo *philo, t_philo_instance *philosopher)
{
    pthread_mutex_lock(philosopher->own_mutex);
    philosopher->state = FORK_TAKEN;
    printf_philo_state(philo, philosopher);
    pthread_mutex_lock(philosopher->other_mutex);
    printf_philo_state(philo, philosopher);
    return TRUE;
}

static void eat(t_philo *philo, t_philo_instance *philosopher)
{
    philosopher->state = EATING;
    printf_philo_state(philo, philosopher);
    msleep(philosopher->time_to_eat); 
    pthread_mutex_unlock(philosopher->own_mutex);
    pthread_mutex_unlock(philosopher->other_mutex);
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
    pthread_mutex_lock(&philosopher->wake_mutex);
    philosopher->wake_time = elapsed_time(philo->params.start_timer);
    pthread_mutex_unlock(&philosopher->wake_mutex);
}

void    philo_routine(t_philo_instance *data)
{
    t_philo     *philo;
    t_boolean   count_eats;

    philo = data->philo;
    pthread_mutex_lock(&philo->params.start_mutex);
    pthread_mutex_unlock(&philo->params.start_mutex);
    if (data->philo_id % 2)
        usleep(200);
    count_eats = FALSE;
    if (data->nbr_of_eats)
        count_eats = TRUE;
    printf("before %d\n", data->die);
    while (!data->die && (!count_eats || data->nbr_of_eats))
    {
        take_forks(philo, data);
        eat(philo, data);
        go_sleep(philo, data);
        think(philo, data);
        data->nbr_of_eats--;
    }
    pthread_mutex_lock(&data->wake_mutex);
    data->die = TRUE;
    pthread_mutex_unlock(&data->wake_mutex);
}

