/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche < tmouche@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:13:15 by tmouche           #+#    #+#             */
/*   Updated: 2024/06/07 03:26:08 by tmouche          ###   ########.fr       */
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
	if (philo->ev_things->simul->simul == OFF)
		exit (EXIT_SUCCESS);
	pthread_mutex_unlock(&philo->ev_things->simul->mutex);
	if (philo->state == DEAD)
	{
		pthread_mutex_lock(&philo->ev_things->simul->mutex);
		philo->ev_things->simul->simul = OFF;
		pthread_mutex_unlock(&philo->ev_things->simul->mutex);
	}
	gettimeofday(&clock, NULL);
	time_stamp = clock.tv_usec / M_SEC + ((clock.tv_sec - timer[0]) * 1000) - timer[1];
	printf("%ld %d %s\n", time_stamp, philo->name, str);
}

static inline void	_thinking(t_philo *philo,  size_t *timer)
{
	if (philo->fhand == 0)
	{
		pthread_mutex_lock(&philo->fork->mutex);
		if (philo->fork->data == TAKEN)
		{
			pthread_mutex_unlock(&philo->fork->mutex);
			return ;
		}
		philo->fork->data = TAKEN;
		pthread_mutex_unlock(&philo->fork->mutex);
		_printer(philo, timer, "has taken a fork");
	}
	pthread_mutex_lock(&philo->next->fork->mutex);
	if (philo->next->fork->data == TAKEN)
	{
		pthread_mutex_unlock(&philo->fork->mutex);
		return ;
	}
	philo->fork->data = TAKEN;
	pthread_mutex_unlock(&philo->fork->mutex);
	_printer(philo, timer, "has taken a fork");
	philo->state = EATING;
	philo->time_to_die = 0;
	_printer(philo, timer, "is eating");
}

static inline void	_sleeping(t_philo *philo, size_t *timer)
{
	++philo->time_to_sleep;
	if (philo->time_to_sleep == philo->args->time_to_sleep)
	{
		philo->time_to_sleep = 0;
		philo->state = THINKING;
		_printer(philo, timer, "is thinking");
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
		pthread_mutex_lock(&philo->fork->mutex);
		philo->fork->data = FREE;
		pthread_mutex_unlock(&philo->fork->mutex);
		pthread_mutex_lock(&philo->next->fork->mutex);
		philo->next->fork->data = FREE;
		pthread_mutex_unlock(&philo->next->fork->mutex);
		philo->fhand = 0;
		philo->state = SLEEPING;
		_printer(philo, timer, "is sleeping");
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
			if (++philo->time_to_die == philo->args->time_to_die)
			{
				philo->state = DEAD;
				_printer(philo, starter, "is dead");
				exit (EXIT_FAILURE);
			}
			if (philo->state == EATING)
				_eating(philo, starter);
			else if (philo->state == SLEEPING)
				_sleeping(philo, starter);
			else
				_thinking(philo, starter);
			temp_usec = clock.tv_usec / M_SEC;
		}
	}
}