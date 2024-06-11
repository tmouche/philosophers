/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche < tmouche@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 02:07:30 by thibaud           #+#    #+#             */
/*   Updated: 2024/06/11 15:47:41 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <unistd.h>
#include <stdlib.h>

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

size_t	ft_strlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

void	_exit_end(t_data *ev_thing, char *str, t_end last)
{
	if (ev_thing)
	{
		// _lstclear(ev_thing->head, 1);
		free(ev_thing->threads);
		pthread_mutex_destroy(&ev_thing->simul->mutex);
		pthread_mutex_destroy(&ev_thing->start->mutex);
	}
	if (last == OFF)
	{
		write(2, str, ft_strlen(str, 0));
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}