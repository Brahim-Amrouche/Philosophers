/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:01:36 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/11 21:10:07 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

void	exit_philo(char *message)
{
	size_t	str_len;
	size_t	i;

	if (!message)
		return ;
	i = -1;
	str_len = ft_strlen(message);
	while (++i < str_len)
		write(2, (message + i), 1);
	exit(1);
}
