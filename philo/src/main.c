/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:57:50 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/20 17:04:02 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static void	set_philo_info(t_philo *philo, int i)
{
	memset(&philo->params.philos_data[i], 0, sizeof(t_philo_instance));
	philo->params.philos_data[i] = philo->philo_info;
	philo->params.philos_data[i].philo_id = i + 1;
	philo->params.philos_data[i].own_mutex = &philo->params.philo_forks[i];
	philo->params.philos_data[i].other_mutex = &philo->params.philo_forks[(i
			+ 1) % (philo->philo_info.philo_id)];
	philo->params.philos_data[i].philo = philo;
	if (pthread_mutex_init(&philo->params.philos_data[i].wake_mutex, NULL))
		exit_philo("couldn't init wake mutex\n", philo);
}

static void	supervisor_helper(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->params.philos_data[i].wake_mutex);
	if (philo->params.philos_data[i].die)
		philo->params.died_count++;
	else if (philo->params.philos_data[i].wake_time
		&& elapsed_time(philo->params.start_timer)
		- philo->params.philos_data[i].wake_time
		>= philo->philo_info.time_to_die)
	{
		pthread_mutex_lock(&philo->params.printf_mutex);
		pthread_mutex_lock(&philo->params.death_mutex);
		if (!philo->death)
			printf("%ld %d died\n",
				elapsed_time(philo->params.start_timer),
				philo->params.philos_data[i].philo_id);
		philo->death = TRUE;
		pthread_mutex_unlock(&philo->params.death_mutex);
		pthread_mutex_unlock(&philo->params.printf_mutex);
	}
	pthread_mutex_unlock(&philo->params.philos_data[i].wake_mutex);
}

static void	supervisor(t_philo *philo)
{
	int	i;

	while (TRUE && !philo->death
		&& philo->params.died_count < philo->philo_info.time_to_die)
	{
		i = 0;
		while (i < philo->philo_info.philo_id)
		{
			supervisor_helper(philo, i);
			i++;
		}
	}
}

static void	initiate_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_info.philo_id)
	{
		set_philo_info(philo, i);
		if (philo->parsing_error)
			return ;
		if (pthread_create(&philo->params.threads_id[i], NULL,
				(void *) philo_routine,
				&philo->params.philos_data[i]))
		{
			exit_philo("couldn't create threads\n", philo);
			return ;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_philo	philo;
	int		i;

	memset(&philo, 0, sizeof(t_philo));
	parse_philo(argc, argv, &philo);
	if (philo.parsing_error)
		return (1);
	mutexes_initiator(&philo);
	if (philo.parsing_error)
		return (1);
	pthread_mutex_lock(&philo.params.start_mutex);
	initiate_threads(&philo);
	if (philo.parsing_error)
		return (1);
	philo.params.start_timer = elapsed_time(0);
	pthread_mutex_unlock(&philo.params.start_mutex);
	supervisor(&philo);
	i = 0;
	while (i < philo.philo_info.philo_id)
		pthread_join(philo.params.threads_id[i++], NULL);
	philo_mem_cleaner(&philo);
	return (0);
}
