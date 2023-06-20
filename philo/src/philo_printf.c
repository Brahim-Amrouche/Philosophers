/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:40:40 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/20 19:59:20 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	printf_philo_state(t_philo *philo, t_philo_instance *philosopher,
	char *message)
{
	pthread_mutex_lock(&philo->params.printf_mutex);
	pthread_mutex_lock(&philo->params.death_mutex);
	pthread_mutex_lock(&philosopher->wake_mutex);
	if (philosopher->die || philo->death)
	{
		philosopher->die = TRUE;
		pthread_mutex_unlock(&philo->params.printf_mutex);
		pthread_mutex_unlock(&philo->params.death_mutex);
		pthread_mutex_unlock(&philosopher->wake_mutex);
		return ;
	}
	pthread_mutex_unlock(&philosopher->wake_mutex);
	pthread_mutex_unlock(&philo->params.death_mutex);
	printf("%ld %d %s\n", elapsed_time(philo->params.start_timer),
		philosopher->philo_id, message);
	pthread_mutex_unlock(&philo->params.printf_mutex);
}

void	init_wake_time(t_philo *philo, t_philo_instance *data)
{
	pthread_mutex_lock(&data->wake_mutex);
	data->wake_time = elapsed_time(philo->params.start_timer);
	pthread_mutex_unlock(&data->wake_mutex);
}
