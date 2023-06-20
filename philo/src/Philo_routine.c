/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:49:25 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/20 19:59:07 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static void	take_forks(t_philo *philo, t_philo_instance *philosopher)
{
	pthread_mutex_lock(philosopher->own_mutex);
	printf_philo_state(philo, philosopher, "has taken a fork");
	if (philo->philo_info.philo_id == 1)
	{
		msleep(philosopher->time_to_die);
		printf_philo_state(philo, philosopher, "died");
		pthread_mutex_lock(&philosopher->wake_mutex);
		philosopher->die = TRUE;
		pthread_mutex_unlock(&philosopher->wake_mutex);
		pthread_mutex_unlock(philosopher->own_mutex);
	}
	pthread_mutex_lock(philosopher->other_mutex);
	printf_philo_state(philo, philosopher, "has taken a fork");
}

static void	eat(t_philo *philo, t_philo_instance *philosopher)
{
	printf_philo_state(philo, philosopher, "is eating");
	pthread_mutex_lock(&philosopher->wake_mutex);
	philosopher->wake_time = elapsed_time(philo->params.start_timer);
	pthread_mutex_unlock(&philosopher->wake_mutex);
	msleep(philosopher->time_to_eat);
	pthread_mutex_unlock(philosopher->own_mutex);
	pthread_mutex_unlock(philosopher->other_mutex);
	philosopher->nbr_of_eats--;
}

static void	go_sleep(t_philo *philo, t_philo_instance *philosopher)
{
	printf_philo_state(philo, philosopher, "is sleeping");
	msleep(philosopher->time_to_sleep);
}

static void	think(t_philo *philo, t_philo_instance *philosopher)
{
	printf_philo_state(philo, philosopher, "is thinking");
}

void	philo_routine(t_philo_instance *data)
{
	t_philo		*philo;
	t_boolean	count_eats;

	philo = data->philo;
	pthread_mutex_lock(&philo->params.start_mutex);
	pthread_mutex_unlock(&philo->params.start_mutex);
	if (data->philo_id % 2)
		usleep(200);
	count_eats = FALSE;
	if (data->nbr_of_eats)
		count_eats = TRUE;
	init_wake_time(philo, data);
	while (!data->die && (!count_eats || data->nbr_of_eats))
	{
		take_forks(philo, data);
		eat(philo, data);
		if (count_eats && !data->nbr_of_eats)
			break ;
		go_sleep(philo, data);
		think(philo, data);
	}
	pthread_mutex_lock(&data->wake_mutex);
	data->die = TRUE;
	pthread_mutex_unlock(&data->wake_mutex);
}
