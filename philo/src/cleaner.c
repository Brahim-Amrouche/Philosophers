/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:49:07 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/17 16:17:09 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	philo_mem_cleaner(t_philo *philo)
{
	int	i;

	pthread_mutex_destroy(&philo->params.printf_mutex);
	pthread_mutex_destroy(&philo->params.death_mutex);
	pthread_mutex_destroy(&philo->params.start_mutex);
	i = 0;
	while (i < philo->philo_info.philo_id)
		pthread_mutex_destroy(&philo->params.philo_forks[i++]);
	i = 0;
	while (i < philo->philo_info.philo_id)
		pthread_mutex_destroy(&philo->params.philos_data[i++].wake_mutex);
	free(philo->params.philo_forks);
	free(philo->params.threads_id);
	free(philo->params.philos_data);
}
