/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:53:41 by tmouche           #+#    #+#             */
/*   Updated: 2024/06/12 14:00:31 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <sys/time.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static inline t_end	_thinking_hand_st(t_philo *philo, size_t timer)
{
	pthread_mutex_lock(&philo->fork->mutex);
	if (philo->fork->data == TAKEN)
		return (pthread_mutex_unlock(&philo->fork->mutex), ON);
	philo->fork->data = TAKEN;
	pthread_mutex_unlock(&philo->fork->mutex);
	if (_printer(philo, timer, "has taken a fork") == OFF)
		return (OFF);
	philo->fhand = 1;
	return (CONTINUE);
}

static inline t_end	_thinking_hand_nd(t_philo *philo, size_t timer,
				size_t act_time)
{
	t_mutex_data	*fork_next;

	fork_next = philo->next->fork;
	pthread_mutex_lock(&fork_next->mutex);
	if (fork_next->data == TAKEN)
		return (pthread_mutex_unlock(&fork_next->mutex), ON);
	fork_next->data = TAKEN;
	pthread_mutex_unlock(&fork_next->mutex);
	if (_printer(philo, timer, "has taken a fork") == OFF)
		return (OFF);
	philo->fhand = 2;
	if (_printer(philo, timer, "is eating") == OFF)
		return (OFF);
	philo->state = EATING;
	philo->time_to_eat = act_time;
	return (ON);
}

inline t_end	_thinking(t_philo *philo, size_t timer, size_t act_time)
{
	t_end	result;

	result = CONTINUE;
	if (philo->fhand == 0)
		result = _thinking_hand_st(philo, timer);
	if (result == CONTINUE)
		result = _thinking_hand_nd(philo, timer, act_time);
	return (result);
}

inline t_end	_sleeping(t_philo *philo, size_t timer, size_t act_time)
{
	if (act_time - philo->time_to_sleep >= philo->args->time_to_sleep)
	{
		if (_printer(philo, timer, "is thinking") == OFF)
			return (OFF);
		philo->state = THINKING;
		return (ON);
	}
	else if (philo->args->time_to_sleep - act_time - philo->time_to_sleep > 1)
		usleep(900);
	return (ON);
}

inline t_end	_eating(t_philo *philo, size_t timer, size_t act_time)
{
	t_mutex_data	*fork;
	t_mutex_data	*fork_next;

	if (act_time - philo->time_to_eat >= philo->args->time_to_eat)
	{
		philo->time_eaten += 1;
		philo->time_to_die = act_time;
		fork = philo->fork;
		fork_next = philo->next->fork;
		pthread_mutex_lock(&fork->mutex);
		philo->fork->data = FREE;
		pthread_mutex_unlock(&fork->mutex);
		pthread_mutex_lock(&fork_next->mutex);
		philo->next->fork->data = FREE;
		pthread_mutex_unlock(&fork_next->mutex);
		philo->fhand = 0;
		if (philo->args->max_time_eat == philo->time_eaten
			|| _printer(philo, timer, "is sleeping") == OFF)
			return (OFF);
		philo->time_to_sleep = act_time;
		philo->state = SLEEPING;
	}
	else if (philo->args->time_to_eat - act_time - philo->time_to_eat > 1)
		usleep(900);
	return (ON);
}
