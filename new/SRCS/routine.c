/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:13:15 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/18 15:45:30 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <sys/time.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static inline void	_printer(size_t *starter, int num_philo, char *str)
{
	struct timeval	clock;
	size_t			time_stamp;

	if (_strchr("is dead", str) == 1)
		return ;
	gettimeofday(&clock, NULL);
	time_stamp = clock.tv_usec / M_SEC + ((clock.tv_sec - starter[0]) * 1000) - starter[1];
	printf("%ld %d %s\n", time_stamp, num_philo, str);
}

static inline void	_thinking(t_philo *philo, size_t *starter)
{
	pthread_mutex_lock(&philo->fork->mutex);
	philo->fork->data = philo->state->fork_taken;
	_printer(starter, philo->rank, "has taken a fork");
	pthread_mutex_lock(&philo->prev->fork->mutex);
	philo->prev->fork->data = philo->state->fork_taken;
	_printer(starter, philo->rank, "has taken a fork");
	philo->status = philo->state->eat;
	philo->time_to_die = 0;
	_printer(starter, philo->rank, "is eating");
}

static inline void	_sleeping(t_philo *philo, size_t *starter)
{
	++philo->time_to_sleep;
	if (philo->time_to_sleep == philo->ref->time_to_sleep)
	{
		philo->time_to_sleep = 0;
		philo->status = philo->state->think;
		_printer(starter, philo->rank, "is thinking");
	}
}

static inline void	_eating(t_philo *philo, size_t *starter)
{
	++philo->time_to_eat;
	if (philo->time_to_eat == philo->ref->time_to_eat)
	{
		++philo->time_eaten;
		philo->time_to_eat = 0;
		if (philo->ref->max_time_eat == philo->time_eaten)
			exit (EXIT_SUCCESS);
		philo->fork->data = philo->state->fork_free;
		philo->prev->fork->data = philo->state->fork_free;
		pthread_mutex_unlock(&philo->fork->mutex);
		pthread_mutex_unlock(&philo->prev->fork->mutex);
		philo->status = philo->state->sleep;
		_printer(starter, philo->rank, "is sleeping");
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
				_printer(starter, philo->rank, "is dead");
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