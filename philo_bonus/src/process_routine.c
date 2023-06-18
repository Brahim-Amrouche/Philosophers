/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:34:28 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/18 14:09:11 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

static void print_philo_state(t_philo_bonus *philo_bonus)
{
    sem_wait(philo_bonus->bonus_params.death_sem);
    if (philo_bonus->philo_info.state == FORK_TAKEN)
        printf("%ld %d has taken a fork\n", elapsed_time(philo_bonus->bonus_params.start_time), philo_bonus->philo_info.philo_id);
    else if (philo_bonus->philo_info.state == EATING)
        printf("%ld %d is eating\n", elapsed_time(philo_bonus->bonus_params.start_time), philo_bonus->philo_info.philo_id);
    else if (philo_bonus->philo_info.state == SLEEPING)
        printf("%ld %d is sleeping\n", elapsed_time(philo_bonus->bonus_params.start_time), philo_bonus->philo_info.philo_id);
    else if (philo_bonus->philo_info.state == THINKING)
        printf("%ld %d is thinking\n", elapsed_time(philo_bonus->bonus_params.start_time), philo_bonus->philo_info.philo_id);
    else if (philo_bonus->philo_info.state == DIED)
    {
        printf("%ld %d died\n", elapsed_time(philo_bonus->bonus_params.start_time), philo_bonus->philo_info.philo_id);
        return;
    }
    sem_post(philo_bonus->bonus_params.death_sem);
}

static  void    take_forks(t_philo_bonus *philo_bonus)
{
    sem_wait(philo_bonus->bonus_params.forks_sem);
    philo_bonus->philo_info.state = FORK_TAKEN;
    print_philo_state(philo_bonus);
    sem_wait(philo_bonus->bonus_params.forks_sem);
    print_philo_state(philo_bonus);
}

static void     eat(t_philo_bonus *philo_bonus)
{
    philo_bonus->philo_info.state = EATING;
    print_philo_state(philo_bonus);
    sem_wait(philo_bonus->bonus_params.eat_time_sem);
    philo_bonus->philo_info.wake_time = elapsed_time(philo_bonus->bonus_params.start_time);
    sem_post(philo_bonus->bonus_params.eat_time_sem);
    msleep(philo_bonus->philo_info.time_to_eat);
    sem_post(philo_bonus->bonus_params.forks_sem);
    sem_post(philo_bonus->bonus_params.forks_sem);
}

static void     philo_sleep(t_philo_bonus *philo_bonus)
{
    philo_bonus->philo_info.state = SLEEPING;
    print_philo_state(philo_bonus);
    msleep(philo_bonus->philo_info.time_to_sleep);
}

static void     thinking(t_philo_bonus *philo_bonus)
{
    philo_bonus->philo_info.state = THINKING;
    print_philo_state(philo_bonus);
}

void    process_supervisor(t_philo_bonus *philo_bonus)
{
    while (TRUE)
    {
        sem_wait(philo_bonus->bonus_params.eat_time_sem);
        if (philo_bonus->philo_info.wake_time)
            break;
        sem_post(philo_bonus->bonus_params.eat_time_sem);
    }
    sem_post(philo_bonus->bonus_params.eat_time_sem);
    while (TRUE)
    {
        sem_wait(philo_bonus->bonus_params.death_sem);
        sem_wait(philo_bonus->bonus_params.eat_time_sem);
        if (elapsed_time(philo_bonus->bonus_params.start_time) - philo_bonus->philo_info.wake_time > philo_bonus->philo_info.time_to_die)
        {
            printf("%ld %d died\n", elapsed_time(philo_bonus->bonus_params.start_time), philo_bonus->philo_info.philo_id);
            break;
        }
        sem_post(philo_bonus->bonus_params.eat_time_sem);
        sem_post(philo_bonus->bonus_params.death_sem);
    }
    exit(1);
}

void    process_routine(t_philo_bonus *philo_bonus)
{
    t_boolean        meal_count;
    pthread_t        supervisor_id;

    sem_wait(philo_bonus->bonus_params.syncro_sem);
    sem_post(philo_bonus->bonus_params.syncro_sem);
    meal_count = FALSE;
    if (philo_bonus->philo_info.nbr_of_eats)
        meal_count = TRUE;
    if (pthread_create(&supervisor_id, NULL, (void *) process_supervisor, philo_bonus))
        exit(1);
    pthread_detach(supervisor_id);
    if (philo_bonus->philo_info.philo_id % 2)
        usleep(300);
    while (!meal_count || philo_bonus->philo_info.nbr_of_eats)
    {
        take_forks(philo_bonus);
        eat(philo_bonus);
        philo_sleep(philo_bonus);
        thinking(philo_bonus);
        philo_bonus->philo_info.nbr_of_eats--;
    }
    exit(0);
}