/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche < tmouche@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:13:15 by tmouche           #+#    #+#             */
/*   Updated: 2024/06/11 16:47:25 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <sys/time.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static inline t_end	_printer(t_philo *philo , size_t *timer, char *str)
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

static inline t_end	_thinking(t_philo *philo,  size_t *timer)
{
	t_fstate	result;
	
	if (philo->fhand == 0)
	{
		pthread_mutex_lock(&philo->fork->mutex);
		result = philo->fork->data;
		pthread_mutex_unlock(&philo->fork->mutex);
		if (result == TAKEN)
			return (ON);
		pthread_mutex_lock(&philo->fork->mutex);
		philo->fork->data = TAKEN;
		pthread_mutex_unlock(&philo->fork->mutex);
		if (_printer(philo, timer, "has taken a fork") == OFF)
			return (OFF);
		philo->fhand = 1;
	}
	pthread_mutex_lock(&philo->next->fork->mutex);
	result = philo->next->fork->data;
	pthread_mutex_unlock(&philo->next->fork->mutex);
	if (result == TAKEN)
		return (ON);
	pthread_mutex_lock(&philo->next->fork->mutex);
	philo->fork->data = TAKEN;
	pthread_mutex_unlock(&philo->next->fork->mutex);
	if (_printer(philo, timer, "has taken a fork") == OFF)
		return (OFF);
	philo->fhand = 2;
	philo->state = EATING;
	return (_printer(philo, timer, "is eating"));
}

static inline t_end	_sleeping(t_philo *philo, size_t *timer)
{
	philo->time_to_sleep += 1;
	if (philo->time_to_sleep == philo->args->time_to_sleep)
	{
		philo->time_to_sleep = 0;
		philo->state = THINKING;
		if (_printer(philo, timer, "is thinking") == OFF)
			return (OFF);
	}
	return (ON);
}

static inline t_end	_eating(t_philo *philo,  size_t *timer)
{
	++philo->time_to_eat;
	if (philo->time_to_eat == philo->args->time_to_eat)
	{
		philo->time_eaten += 1;
		philo->time_to_eat = 0;
		philo->time_to_die = 0;
		pthread_mutex_lock(&philo->fork->mutex);
		philo->fork->data = FREE;
		pthread_mutex_unlock(&philo->fork->mutex);
		pthread_mutex_lock(&philo->next->fork->mutex);
		philo->next->fork->data = FREE;
		pthread_mutex_unlock(&philo->next->fork->mutex);
		philo->fhand = 0;
		if (philo->args->max_time_eat == philo->time_eaten)
			return (OFF);
		philo->state = SLEEPING;
		if (_printer(philo, timer, "is sleeping") == OFF)
			return (OFF);
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
		gettimeofday(&clock, NULL);
		if (temp_usec != clock.tv_usec / M_SEC)
		{
			philo->time_to_die += 1;
			if (philo->time_to_die == philo->args->time_to_die)
			{
				philo->state = DEAD;
				if (_printer(philo, starter, "is dead") == OFF)
					return (NULL);
			}
			if (philo->state == EATING && )
			{
				if (_eating(philo, starter) == OFF)
					return (NULL);
			}
			else if (philo->state == SLEEPING)
			{
				if (_sleeping(philo, starter) == OFF)
					return (NULL);
			}
			else
			{
				if (_thinking(philo, starter) == OFF)
					return (NULL);
			}
			temp_usec = clock.tv_usec / M_SEC;
		}
		
	}
}
