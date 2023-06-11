/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:01:16 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/11 21:10:31 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

    if(!s)
        return (0);
	i = -1;
	while (s[++i])
		;
	return (i);
}