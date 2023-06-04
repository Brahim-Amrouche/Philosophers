/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:01:36 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/04 18:45:11 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void    exit_philo(char *message, t_philo *philo)
{
    size_t	str_len;
	size_t	i;

	if (!message)
		return ;
	i = -1;
	str_len = ft_strlen(message);
	while (++i < str_len)
		write(2, (message + i), 1);
	philo->parsing_error = TRUE;
}

