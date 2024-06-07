/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche < tmouche@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:54:57 by tmouche           #+#    #+#             */
/*   Updated: 2024/06/07 03:33:39 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static void	*_monitoring(void *args)
{
	
}

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_base		ref;
	t_state		state;
	pthread_t	*threads;
	
	if (ac < 5 || ac > 6)
		return (_write_error(0), -1);
	_init_state(&state);
	_init_reference(&ref, av, ac);
	philo = NULL;
	_init_philo(&ref, &state, &philo);
	threads = malloc(sizeof(pthread_t) * (ref.philos + 1));
	if (!threads)
		return (_lstclear(&philo), -1);
	_philo_exec(philo, threads, &ref);
	return (0);
}