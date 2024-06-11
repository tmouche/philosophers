/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche < tmouche@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:13:15 by tmouche           #+#    #+#             */
/*   Updated: 2024/06/11 17:38:59 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <sys/time.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

inline t_end	_printer(t_philo *philo , size_t *timer, char *str)
{
	struct timeval	clock;
	size_t			time_stamp;
	t_end			result;
	
	pthread_mutex_lock(&philo->ev_things->simul->mutex);
	result = philo->ev_things->simul->simul;
	pthread_mutex_unlock(&philo->ev_things->simul->mutex);
	if (result == OFF)
		return (OFF);
	if (philo->state == DEAD)
	{
		pthread_mutex_lock(&philo->ev_things->simul->mutex);
		philo->ev_things->simul->simul = OFF;
		pthread_mutex_unlock(&philo->ev_things->simul->mutex);
		result = OFF;
	}
	gettimeofday(&clock, NULL);
	time_stamp = clock.tv_usec / M_SEC + ((clock.tv_sec - timer[0]) * 1000) - timer[1];
	pthread_mutex_lock(&philo->ev_things->start->mutex);
	printf("%ld %d %s\n", time_stamp, philo->name, str);
	pthread_mutex_unlock(&philo->ev_things->start->mutex);
	return (result);
}

static inline t_end	_routine_exec(t_philo *philo, int *temp_usec, size_t *starter)
{
	struct timeval	clock;

	gettimeofday(&clock, NULL);
	if (*temp_usec != clock.tv_usec / M_SEC)
	{
		philo->time_to_die += 1;
		if (philo->time_to_die == philo->args->time_to_die)
		{
			philo->state = DEAD;
			if (_printer(philo, starter, "is dead") == OFF)
				return (OFF);
		}
		if (philo->state == EATING && _eating(philo, starter) == OFF)
			return (OFF);
		else if (philo->state == SLEEPING && _sleeping(philo, starter) == OFF)
			return (OFF);
		else if (philo->state == THINKING && _thinking(philo, starter) == OFF)
			return (OFF);
		*temp_usec = clock.tv_usec / M_SEC;
	}
	return (ON);
}

void	*_routine(void *args)
{
	struct timeval	clock;
	t_philo			*philo;
	size_t			starter[2];
	int				temp_usec;
	
	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->ev_things->start->mutex);
	pthread_mutex_unlock(&philo->ev_things->start->mutex);
	gettimeofday(&clock, NULL);
	starter[0] = clock.tv_sec;
	starter[1] = clock.tv_usec / M_SEC;
	temp_usec = clock.tv_usec / M_SEC;
	while (1)
	{
		if (_routine_exec(philo, &temp_usec, starter) == OFF)
			return (NULL);
	}
}
