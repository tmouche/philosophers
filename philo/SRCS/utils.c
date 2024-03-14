/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:07:48 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/14 16:27:27 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <sys/time.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void	*_clocker(void *args)
{
	struct timeval	clock;
	t_mutex_data	*mutex;
	int				cloker[2];

	clocker = (t_clocker *)args;
	mutex = malloc(sizeof(t_mutex_data));
	if (!mutex)
		exit (EXIT_FAILURE);
	while (1)
	{
		gettimeofday(&clock, NULL);
		clocker->m_sec = clock.tv_usec / M_SEC;
		clocker->sec = clock.tv_sec / M_SEC;
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
