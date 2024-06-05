/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 02:02:42 by thibaud           #+#    #+#             */
/*   Updated: 2024/06/05 19:43:17 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <sys/time.h>
#include <string.h>

void	_init_argument(t_ref *args, char **av, int ac)
{
	int	temp[5];
	int	i;

	i = 0;
	memset(temp, -1, 5);
	while (i < ac)
	{
		temp[i] = _atoi(av[i + 1]);
		if (temp[i] == -1)
			_exit_failure(NULL, "Error : Invalid argument\n");
		++i;
	}
	args->philos = temp[1];
	args->time_to_die = temp[2];
	args->time_to_eat = temp[3];
	args->time_to_sleep = temp[4];
	if (temp[5] != -1)
		args->max_time_eat = temp[5];
}

void	*_stopwatch(void *time)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	if (*(int *)time != tv.tv_usec * M_SEC)
		*(int *)time = tv.tv_usec * M_SEC;
}

void	_philo_exec(t_data *ev_thing, pthread_t *threads)
{
	int	i;
	
	if (pthread_create(&threads[0], NULL, _stopwatch, &ev_thing->time) != 0)
	i = 1;
	while (i <= )
	{
		if (pthread_create(&threads[i], NULL, _routine, philo) != 0)
			_exit_failure(ev_thing, "Pthread failed\n");
		philo = philo->next;
		++i;
	}
}

int	main(int ac, char **av)
{
	pthread_t	*threads;
	t_data		ev_thing;
	t_ref		args;
	
	if (ac < 5 || ac > 6)
		_exit_failure(NULL, "error : Incorrect number of arguments\n");
	_init_argument(&args, av, ac);
	threads = malloc(sizeof(pthread_t) * (args.philos + 1));
	if (!threads)
		return (-1);
	ev_thing.head = _init_philos(&ev_thing, &args);
	if (!ev_thing.head)
		return (free(threads), -1);
	ev_thing.threads = threads;
	ev_thing.args = &args;
	_philo_exec();
	
	
	
}