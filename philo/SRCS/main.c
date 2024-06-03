/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:54:57 by tmouche           #+#    #+#             */
/*   Updated: 2024/06/03 18:51:58 by thibaud          ###   ########.fr       */
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