/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche < tmouche@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:53:41 by tmouche           #+#    #+#             */
/*   Updated: 2024/06/11 17:36:51 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <sys/time.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static inline t_end	_thinking_hand_st(t_philo *philo,  size_t *timer)
{
	t_fstate	result;
	
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
	return (CONTINUE);
}

static inline t_end	_thinking_hand_nd(t_philo *philo,  size_t *timer)
{
	t_fstate	result;

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
	if (_printer(philo, timer, "is eating") == OFF)
		return (OFF);
	philo->state = EATING;
	return (ON);
}

inline t_end	_thinking(t_philo *philo,  size_t *timer)
{
	t_end	result;

	result = CONTINUE;
	if (philo->fhand == 0)
		result = _thinking_hand_st(philo, timer);
	if (result == CONTINUE)
		result = _thinking_hand_nd(philo, timer);
	return (result);
}

inline t_end	_sleeping(t_philo *philo, size_t *timer)
{
	philo->time_to_sleep += 1;
	if (philo->time_to_sleep == philo->args->time_to_sleep)
	{
		philo->time_to_sleep = 0;
		if (_printer(philo, timer, "is thinking") == OFF)
			return (OFF);
		philo->state = THINKING;
	}
	return (ON);
}

inline t_end	_eating(t_philo *philo,  size_t *timer)
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
		if (_printer(philo, timer, "is sleeping") == OFF)
			return (OFF);
		philo->state = SLEEPING;
	}
	return (ON);
}