/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:13:15 by tmouche           #+#    #+#             */
/*   Updated: 2024/06/06 20:05:18 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <sys/time.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static inline void	_printer(t_philo *philo , size_t *timer, char *str)
{
	struct timeval	clock;
	size_t			time_stamp;
	
	pthread_mutex_lock(&philo->ev_things->simul->mutex);
	if (&philo->ev_things->simul->mutex == OFF)
		exit (EXIT_SUCCESS);
	pthread_mutex_unlock(&philo->ev_things->simul->mutex);
	if (philo->state == DEAD)
	{
		pthread_mutex_lock(&philo->ev_things->simul->mutex);
		&philo->ev_things->simul->mutex == OFF;
		pthread_mutex_unlock(&philo->ev_things->simul->mutex);
	}
	gettimeofday(&clock, NULL);
	time_stamp = clock.tv_usec / M_SEC + ((clock.tv_sec - timer[0]) * 1000) - timer[1];
	printf("%ld %d %s\n", timer, philo->name, str);
}

static inline void	_thinking(t_philo *philo,  size_t *timer)
{
	pthread_mutex_lock(&philo->fork->mutex);
	philo->fork->data = TAKEN;
	_printer(timer, philo->name, "has taken a fork");
	pthread_mutex_lock(&philo->prev->fork->mutex);
	philo->prev->fork->data = TAKEN;
	_printer(timer, philo->name, "has taken a fork");
	philo->state = EATING;
	philo->time_to_die = 0;
	_printer(timer, philo->name, "is eating");
}

static inline void	_sleeping(t_philo *philo, size_t *timer)
{
	++philo->time_to_sleep;
	if (philo->time_to_sleep == philo->args->time_to_sleep)
	{
		philo->time_to_sleep = 0;
		philo->state = THINKING;
		_printer(timer, philo->name, "is thinking");
	}
}

static inline void	_eating(t_philo *philo,  size_t *timer)
{
	++philo->time_to_eat;
	if (philo->time_to_eat == philo->args->time_to_eat)
	{
		++philo->time_eaten;
		philo->time_to_eat = 0;
		if (philo->args->max_time_eat == philo->time_eaten)
			exit (EXIT_SUCCESS);
		philo->fork->data = FREE;
		philo->prev->fork->data = FREE;
		pthread_mutex_unlock(&philo->fork->mutex);
		pthread_mutex_unlock(&philo->prev->fork->mutex);
		philo->state = SLEEPING;
		_printer(timer, philo->name, "is sleeping");
	}
}

void	*_routine(void *args)
{
	struct timeval	clock;
	t_philo			*philo;
	size_t			starter[2];
	int				temp_usec;
	
	philo = (t_philo *)args;
	gettimeofday(&clock, NULL);
	starter[0] = clock.tv_sec;
	starter[1] = clock.tv_usec / M_SEC;
	temp_usec = clock.tv_usec / M_SEC;
	while (1)
	{
		gettimeofday(&clock, NULL);
		if (temp_usec != clock.tv_usec / M_SEC)
		{
			if (++philo->time_to_die == philo->ref->time_to_die)
			{
				_printer(starter, philo->name, "is dead");
				exit (EXIT_FAILURE);
			}
			if (philo->status == philo->state->eat)
				_eating(philo, starter);
			else if (philo->status == philo->state->sleep)
				_sleeping(philo, starter);
			else
				_thinking(philo, starter);
			temp_usec = clock.tv_usec / M_SEC;
		}
	}
}