/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Process_routine_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:12:23 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/19 20:23:29 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

void	print_philo_state(t_philo_bonus *philo_bonus)
{
	sem_wait(philo_bonus->bonus_params.death_sem);
	if (philo_bonus->philo_info.state == FORK_TAKEN)
		printf("%ld %d has taken a fork\n",
			elapsed_time(philo_bonus->bonus_params.start_time),
			philo_bonus->philo_info.philo_id);
	else if (philo_bonus->philo_info.state == EATING)
		printf("%ld %d is eating\n",
			elapsed_time(philo_bonus->bonus_params.start_time),
			philo_bonus->philo_info.philo_id);
	else if (philo_bonus->philo_info.state == SLEEPING)
		printf("%ld %d is sleeping\n",
			elapsed_time(philo_bonus->bonus_params.start_time),
			philo_bonus->philo_info.philo_id);
	else if (philo_bonus->philo_info.state == THINKING)
		printf("%ld %d is thinking\n",
			elapsed_time(philo_bonus->bonus_params.start_time),
			philo_bonus->philo_info.philo_id);
	else if (philo_bonus->philo_info.state == DIED)
	{
		printf("%ld %d died\n",
			elapsed_time(philo_bonus->bonus_params.start_time),
			philo_bonus->philo_info.philo_id);
		return ;
	}
	sem_post(philo_bonus->bonus_params.death_sem);
}

void	process_supervisor(t_philo_bonus *philo_bonus)
{
	while (TRUE)
	{
		sem_wait(philo_bonus->bonus_params.death_sem);
		sem_wait(philo_bonus->bonus_params.eat_time_sem);
		if (philo_bonus->philo_info.count_meals
			&& !philo_bonus->philo_info.nbr_of_eats)
		{
			sem_post(philo_bonus->bonus_params.eat_time_sem);
			sem_post(philo_bonus->bonus_params.death_sem);
			exit(0);
		}
		if (philo_bonus->philo_info.wake_time
			&& elapsed_time(philo_bonus->bonus_params.start_time)
			- philo_bonus->philo_info.wake_time
			> philo_bonus->philo_info.time_to_die)
		{
			printf("%ld %d died\n",
				elapsed_time(philo_bonus->bonus_params.start_time),
				philo_bonus->philo_info.philo_id);
			break ;
		}
		sem_post(philo_bonus->bonus_params.eat_time_sem);
		sem_post(philo_bonus->bonus_params.death_sem);
	}
	exit(1);
}
