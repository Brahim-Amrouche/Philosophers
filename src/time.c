/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamrouch <bamrouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:04:58 by bamrouch          #+#    #+#             */
/*   Updated: 2023/06/04 18:18:54 by bamrouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

time_t elapsed_time(time_t start)
{
    struct timeval current;

    gettimeofday(&current , NULL);
    return ((current.tv_sec * 1000) + (current.tv_usec / 1000) - start);   
}
