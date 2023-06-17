/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:28:37 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/01 14:52:11 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v')
		return (1);
	return (0);
}

t_boolean	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	return (FALSE);
}

long	ft_atoi(const char *str)
{
	int				i;
	unsigned long	res;
	int				sign;

	res = 0;
	i = -1;
	sign = 1;
	while (ft_isspace(*(str + (++i))))
		;
	if (*(str + i) == '+' || *(str + i) == '-')
	{
		if (*(str + i) == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(*(str + i)))
	{
		res = (10 * res) + ((*(str + i)) - '0');
		if (res >= ULLONG_MAX && sign == 1)
			return (-1);
		else if (res >= ULLONG_MAX && sign == -1)
			return (0);
		i++;
	}
	return (res * sign);
}
