/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:22:15 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/17 16:26:47 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

t_boolean	ft_str_is_integer(const char *str, int *res)
{
	int		i;
	long	temp;
	long	is_neg;

	is_neg = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			is_neg = -1;
		str++;
	}
	if (!ft_isdigit(*str))
		return (FALSE);
	while (*str == '0')
		str++;
	i = 0;
	while (str[i])
		if (i > 10 || !ft_isdigit(str[i++]))
			return (FALSE);
	temp = ft_atoi(str) * is_neg;
	if (temp > INT_MAX || temp < INT_MIN)
		return (FALSE);
	*res = (int)temp;
	return (TRUE);
}

void	parse_philo(int argc, char *argv[], t_philo *philo)
{
	if (argc > 6)
		exit_philo("too many arguments\n", philo);
	else if (argc < 5)
		exit_philo("too little arguments\n", philo);
	else if (!ft_str_is_integer(argv[1], &philo->philo_info.philo_id)
		|| philo->philo_info.philo_id <= 0)
		exit_philo("Wrong number of philosophers\n", philo);
	else if (!ft_str_is_integer(argv[2], &philo->philo_info.time_to_die)
		|| philo->philo_info.time_to_die <= 0)
		exit_philo("Wrong time to die\n", philo);
	else if (!ft_str_is_integer(argv[3], &philo->philo_info.time_to_eat)
		|| philo->philo_info.time_to_eat <= 0)
		exit_philo("Wrong time to eat\n", philo);
	else if (!ft_str_is_integer(argv[4], &philo->philo_info.time_to_sleep)
		|| philo->philo_info.time_to_sleep <= 0)
		exit_philo("Wrong time to sleep\n", philo);
	else if (argc == 6 && (!ft_str_is_integer(argv[5],
				&philo->philo_info.nbr_of_eats)
			|| philo->philo_info.nbr_of_eats <= 0))
		exit_philo("Wrong number of eats\n", philo);
}
