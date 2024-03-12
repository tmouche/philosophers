/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:54:57 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/12 19:11:57 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void	_write_error(int num)
{
	printf("Error : ");
	if (num == 0)
		printf("Incorrect number of arguments\n");
	else if (num == 1)
		printf("Invalid argument\n");
	exit (EXIT_FAILURE);
}

static void	_init_reference(t_base *ref, char **av, int ac)
{
	ref->philos = _atoi(av[1]);
	ref->time_to_die = _atoi(av[2]);
	ref->time_to_eat = _atoi(av[3]);
	ref->time_to_sleep = _atoi(av[4]);
	if (ac == 6)
	{
		ref->max_time_eat = _atoi(av[5]);
		if (ref->max_time_eat == -1)
			_write_error(1);
	}
	else
		ref->max_time_eat = -1;
	if (ref->philos == -1 || ref->time_to_die == -1 || ref->time_to_eat == -1
		|| ref->time_to_sleep == -1 || ref->philos > INT_MAX
		|| ref->time_to_die > INT_MAX || ref->time_to_eat > INT_MAX
		|| ref->time_to_sleep > INT_MAX)
		_write_error(1);
}

static t_philo **_init_philo(t_base *ref, t_philo **philo)
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
		if (pthread_mutex_init(&temp->status->mutex, NULL) != 0)
			_lstclear(philo);
		if (temp->rank == 1)
			temp->status->data = 't';
		else
		{
			if (temp->prev->status->data != 'e' &&  temp->next->status->data != 'e')
			temp->status->data = 'e';
			else
				temp->status->data = 't';
		}
	}
	return (philo);
}

static void	_philo_exec(t_philo *philo, pthread_t *threads, t_base *ref)
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
	i = 0;
	while (i < 5)
	{
		pthread_join(threads[i], NULL);
		++i;
	}
	
}

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_base		ref;
	pthread_t	*threads;
	
	if (ac < 5 || ac > 6)
		return (_write_error(0), -1);
	_init_reference(&ref, av, ac);
	philo = NULL;
	_init_philo(&ref, &philo);
	threads = malloc(sizeof(pthread_t) * ref.philos);
	if (!threads)
		return (_lstclear(&philo), -1);
	_philo_exec(philo, threads, &ref);
	return (0);
}