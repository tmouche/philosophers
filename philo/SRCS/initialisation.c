/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:12:50 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/18 15:22:58 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void	_init_reference(t_base *ref, char **av, int ac)
{
	ref->philos = _atoi(av[1]);
	ref->time_to_die = _atoi(av[2]);
	ref->time_to_eat = _atoi(av[3]);
	ref->time_to_sleep = _atoi(av[4]);
	if (ac == 6)
	{
		ref->max_time_eat = _atoi(av[5]);
		if (ref->max_time_eat == 0)
			_write_error(1);
	}
	else
		ref->max_time_eat = 5000;
	if (ref->philos == -1 || ref->time_to_die == -1 || ref->time_to_eat == -1
		|| ref->time_to_sleep == -1 || ref->philos > INT_MAX
		|| ref->time_to_die > INT_MAX || ref->time_to_eat > INT_MAX
		|| ref->time_to_sleep > INT_MAX)
		_write_error(1);
}

void	_init_philo_status(t_state *state, t_philo *philo)
{
	philo->state = state;
	if (philo->prev->fork->data == state->fork_free && philo->rank != 1)
	{
		pthread_mutex_lock(&philo->fork->mutex);
		philo->fork->data = state->fork_taken;
		printf("%d %d has taken a fork\n", 0, philo->rank);
		pthread_mutex_lock(&philo->prev->fork->mutex);
		philo->prev->fork->data = state->fork_taken;
		printf("%d %d has taken a fork\n", 0, philo->rank);
		philo->status = philo->state->eat;
		printf("%d %d is eating\n", 0, philo->rank);
	}
	else
	{
		philo->status = state->think;
		philo->fork->data = state->fork_free;
		printf("%d %d is thinking\n", 0, philo->rank);
	}
}

t_philo **_init_philo(t_base *ref, t_state *state, t_philo **philo)
{
	t_philo	*temp;
	int 	i;
	
	i = 0;
	while (++i <= ref->philos)
	{
		temp = _lstnew(ref, i);
		if (!temp)
			_lstclear(philo);
		_lstadd_back(philo, temp);
		if (pthread_mutex_init(&temp->fork->mutex, NULL) != 0)
			_lstclear(philo);
		_init_philo_status(state, temp);
	}
	return (philo);
}

void	_philo_exec(t_philo *philo, pthread_t *threads, t_base *ref)
{
	int	i;

	i = 0;
	while (i < ref->philos)
	{
		if (pthread_create(&threads[i], NULL, _routine, philo) != 0)
		{
			free(threads);
			_lstclear(&philo);
			exit (EXIT_FAILURE);
		}
		philo = philo->next;
		++i;
	}
}
