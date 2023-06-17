/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:24:43 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/17 16:01:49 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	mutexes_initiator(t_philo *philo)
{
	int	i;

	philo->params.philo_forks = malloc(sizeof(pthread_mutex_t)
			* philo->philo_info.philo_id);
	if (!philo->params.philo_forks)
		exit_philo("couldn't malloc philo forks\n", philo);
	philo->params.threads_id = malloc(sizeof(pthread_t)
			* philo->philo_info.philo_id);
	if (!philo->params.threads_id)
		exit_philo("couldn't malloc enough threads ids", philo);
	philo->params.philos_data = malloc(sizeof(t_philo_instance)
			* philo->philo_info.philo_id);
	if (!philo->params.philos_data)
		exit_philo("couldn't malloc enough philo data \n", philo);
	if (pthread_mutex_init(&philo->params.printf_mutex, NULL))
		exit_philo("couldn't init printf mutex\n", philo);
	if (pthread_mutex_init(&philo->params.start_mutex, NULL))
		exit_philo("couldn't init start mutex\n", philo);
	if (pthread_mutex_init(&philo->params.death_mutex, NULL))
		exit_philo("couldn't init deat_mutex\n", philo);
	i = 0;
	while (i < philo->philo_info.philo_id)
		if (pthread_mutex_init(&philo->params.philo_forks[i++], NULL))
			exit_philo("couldnt init a philo fork mutex\n", philo);
}
