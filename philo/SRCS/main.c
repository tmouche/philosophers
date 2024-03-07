/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:54:57 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/07 16:44:21 by tmouche          ###   ########.fr       */
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

void	_init_philo(t_base *ref, t_philo **philo)
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
	}
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_base	ref;
	
	if (ac < 5 || ac > 6)
		return (_write_error(0), -1);
	printf("%s", av[1]);
	_init_reference(&ref, av, ac);
	_init_philo(&ref ,&philo);
	while (ref.philos > 0)
	{
		printf("%li\n", philo->rank);
		--ref.philos;
		philo = philo->next;
	}
	return (0);
}