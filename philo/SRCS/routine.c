/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:13:15 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/12 19:22:32 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <sys/time.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static inline void	_thinking(t_philo *philo, int time_stamp)
{
	int	stop;

	stop = 0;
	pthread_mutex_lock(&philo->next->status->mutex);
	pthread_mutex_lock(&philo->prev->status->mutex);
	if (philo->next->status->data != 'e' && philo->prev->status->data != 'e')
		stop = 1;
	pthread_mutex_unlock(&philo->next->status->mutex);
	pthread_mutex_unlock(&philo->prev->status->mutex);
	if (stop == 1)
	{
		pthread_mutex_lock(&philo->status->mutex);
		philo->status->data = 'e';
		pthread_mutex_unlock(&philo->status->mutex);
		printf("%d %ld is eating\n", time_stamp, philo->rank);
		philo->time_to_die = 0;
	}
}

static inline void	_sleeping(t_philo *philo, int time_stamp)
{
	++philo->time_to_sleep;
	if (philo->time_to_sleep == philo->ref_t_to_sleep)
	{
		pthread_mutex_lock(&philo->status->mutex);
		philo->status->data = 't';
		pthread_mutex_unlock(&philo->status->mutex);
		printf("%d %ld is thinking\n", time_stamp, philo->rank);
		philo->time_to_sleep = 0;
	}
}

static inline void	_eating(t_philo *philo, int time_stamp)
{
	++philo->time_to_eat;
	if (philo->time_to_eat == philo->ref_t_to_eat)
	{
		++philo->time_eaten;
		if (philo->ref_mt_eat == philo->time_eaten)
			exit (EXIT_SUCCESS);
		pthread_mutex_lock(&philo->status->mutex);
		philo->status->data = 's';
		pthread_mutex_unlock(&philo->status->mutex);
		printf("%d %ld is sleeping\n", time_stamp, philo->rank);
		philo->time_to_eat = 0;
	}
}

void	*_routine(void *args)
{
	struct timeval	clock;
	t_philo			*philo;
	int				temp;
	
	philo = (t_philo *)args;
	gettimeofday(&clock, NULL);
	temp = clock.tv_usec / M_SEC;
	printf("ok value[%ld]", philo->ref_t_to_eat);
	while (1)
	{
		gettimeofday(&clock, NULL);
		if (temp != clock.tv_usec / M_SEC)
		{
			if (++philo->time_to_die == philo->ref_t_to_die)
				exit (EXIT_FAILURE);
			if (philo->status->data == 'e')
				_eating(philo, clock.tv_usec / M_SEC);
			else if (philo->status->data == 's')
				_sleeping(philo, clock.tv_usec / M_SEC);
			else
				_thinking(philo, clock.tv_usec / M_SEC);
			temp = clock.tv_usec / M_SEC;
		}
	}
}