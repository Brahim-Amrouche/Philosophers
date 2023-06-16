/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:04:58 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/12 16:06:25 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers_bonus.h"

void    msleep(time_t delay)
{
    time_t n;

    n = delay;
    while (n--)
        usleep(1000);
}

time_t elapsed_time(time_t start)
{
    struct timeval current;

    gettimeofday(&current , NULL);
    return ((current.tv_sec * 1000) + (current.tv_usec / 1000) - start);   
}