/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:07:48 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/18 15:47:02 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <sys/time.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int	_strchr(char *src, char *str)
{
	int	i_src;
	int	i_str;

	i = 0;
	while (src[i])
	{
		if (src[i])
	}
}

void	_write_error(int num)
{
	printf("Error : ");
	if (num == 0)
		printf("Incorrect number of arguments\n");
	else if (num == 1)
		printf("Invalid argument\n");
	exit (EXIT_FAILURE);
}

void	_init_state(t_state *state)
{
	static int	eat;
	static int	sleep;
	static int	think;
	static int	fork_free;
	static int	fork_taken;
	
	state->eat = &eat;
	state->sleep = &sleep;
	state->think = &think;
	state->fork_free = &fork_free;
	state->fork_taken = &fork_taken;
}

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
