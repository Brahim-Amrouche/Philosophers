/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:34:28 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/19 20:21:54 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

static void	take_forks(t_philo_bonus *philo_bonus)
{
	sem_wait(philo_bonus->bonus_params.forks_sem);
	philo_bonus->philo_info.state = FORK_TAKEN;
	print_philo_state(philo_bonus);
	sem_wait(philo_bonus->bonus_params.forks_sem);
	print_philo_state(philo_bonus);
}

static void	eat(t_philo_bonus *philo_bonus)
{
	philo_bonus->philo_info.state = EATING;
	print_philo_state(philo_bonus);
	sem_wait(philo_bonus->bonus_params.eat_time_sem);
	philo_bonus->philo_info.wake_time
		= elapsed_time(philo_bonus->bonus_params.start_time);
	sem_post(philo_bonus->bonus_params.eat_time_sem);
	msleep(philo_bonus->philo_info.time_to_eat);
	sem_post(philo_bonus->bonus_params.forks_sem);
	sem_post(philo_bonus->bonus_params.forks_sem);
	sem_wait(philo_bonus->bonus_params.eat_time_sem);
	philo_bonus->philo_info.nbr_of_eats--;
	sem_post(philo_bonus->bonus_params.eat_time_sem);
}

static void	philo_sleep(t_philo_bonus *philo_bonus)
{
	philo_bonus->philo_info.state = SLEEPING;
	print_philo_state(philo_bonus);
	msleep(philo_bonus->philo_info.time_to_sleep);
}

static void	thinking(t_philo_bonus *philo_bonus)
{
	philo_bonus->philo_info.state = THINKING;
	print_philo_state(philo_bonus);
}

void	process_routine(t_philo_bonus *philo_bonus)
{
	pthread_t	supervisor_id;

	sem_wait(philo_bonus->bonus_params.syncro_sem);
	sem_post(philo_bonus->bonus_params.syncro_sem);
	if (pthread_create(&supervisor_id, NULL, (void *)process_supervisor,
			philo_bonus))
		exit(1);
	pthread_detach(supervisor_id);
	if (philo_bonus->philo_info.philo_id % 2)
		usleep(500);
	while (TRUE)
	{
		take_forks(philo_bonus);
		eat(philo_bonus);
		if (philo_bonus->philo_info.count_meals
			&& !philo_bonus->philo_info.nbr_of_eats)
			msleep(philo_bonus->philo_info.time_to_sleep
				+ philo_bonus->philo_info.time_to_eat);
		philo_sleep(philo_bonus);
		thinking(philo_bonus);
	}
}
