/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:13:15 by tmouche           #+#    #+#             */
/*   Updated: 2024/06/12 13:59:45 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <sys/time.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

inline t_end	_printer(t_philo *philo, size_t timer, char *str)
{
	struct timeval	sw;
	size_t			time_stamp;
	t_end			result;

	result = ON;
	gettimeofday(&sw, NULL);
	pthread_mutex_lock(&philo->ev_things->simul->mutex);
	if (philo->ev_things->simul->simul != 0)
		return (pthread_mutex_unlock(&philo->ev_things->simul->mutex), OFF);
	pthread_mutex_unlock(&philo->ev_things->simul->mutex);
	if (philo->state == DEAD)
	{
		pthread_mutex_lock(&philo->ev_things->simul->mutex);
		philo->ev_things->simul->simul += 1;
		if (philo->ev_things->simul->simul > 1)
			return (pthread_mutex_unlock(&philo->ev_things->simul->mutex), OFF);
		pthread_mutex_unlock(&philo->ev_things->simul->mutex);
		result = OFF;
	}
	time_stamp = (sw.tv_sec * MS + sw.tv_usec / MS) - timer;
	pthread_mutex_lock(&philo->ev_things->start->mutex);
	printf("%ld %d %s\n", time_stamp, philo->name, str);
	pthread_mutex_unlock(&philo->ev_things->start->mutex);
	usleep(10);
	return (result);
}

static inline t_end	_routine_exec(t_philo *philo, size_t *temp_usec,
					size_t starter)
{
	struct timeval	clock;
	size_t			act_time;

	gettimeofday(&clock, NULL);
	act_time = clock.tv_sec * MS + clock.tv_usec / MS;
	if (*temp_usec != act_time)
	{
		if (act_time - philo->time_to_die >= philo->args->time_to_die)
		{
			philo->state = DEAD;
			if (_printer(philo, starter, "is dead") == OFF)
				return (OFF);
		}
		if (philo->state == EATING
			&& _eating(philo, starter, act_time) == OFF)
			return (OFF);
		else if (philo->state == SLEEPING
			&& _sleeping(philo, starter, act_time) == OFF)
			return (OFF);
		else if (philo->state == THINKING
			&& _thinking(philo, starter, act_time) == OFF)
			return (OFF);
		*temp_usec = act_time;
	}
	return (ON);
}

void	*_routine(void *args)
{
	struct timeval	clock;
	t_philo			*philo;
	size_t			starter;
	size_t			temp_usec;

	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->ev_things->start->mutex);
	pthread_mutex_unlock(&philo->ev_things->start->mutex);
	gettimeofday(&clock, NULL);
	starter = clock.tv_sec * MS + clock.tv_usec / MS;
	temp_usec = starter;
	philo->time_to_die = temp_usec;
	philo->time_to_eat = temp_usec;
	while (1)
	{
		usleep(50);
		if (_routine_exec(philo, &temp_usec, starter) == OFF)
			return (NULL);
	}
}
