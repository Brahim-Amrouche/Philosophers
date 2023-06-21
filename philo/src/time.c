/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:04:58 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/21 17:51:03 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	msleep(time_t delay, t_philo *philo
			, t_philo_instance *philosopher)
{
	time_t	curr_time;

	curr_time = elapsed_time(philo->params.start_timer);
	pthread_mutex_lock(&philosopher->wake_mutex);
	if (philosopher->wake_time + philosopher->time_to_die < curr_time + delay)
		delay = philosopher->wake_time
			+ philosopher->time_to_die - curr_time + 1;
	pthread_mutex_unlock(&philosopher->wake_mutex);
	usleep(delay * 900);
	while (elapsed_time(philo->params.start_timer) - curr_time < delay)
		usleep(500);
}

time_t	elapsed_time(time_t start)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000) + (current.tv_usec / 1000) - start);
}
