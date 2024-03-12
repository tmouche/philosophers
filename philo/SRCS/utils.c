/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:07:48 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/08 16:33:04 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <stdio.h>

ssize_t	_atoi(char *str)
{
	int		i;
	ssize_t	res;

	i = 0;
	res = 0;
	if (str[i] == '+')
		++i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10; 
		res += (str[i] - 48);
		++i;
	}
	if (str[i] != 0)
		return (-1);
	return (res);
}
