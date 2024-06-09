/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 02:02:42 by thibaud           #+#    #+#             */
/*   Updated: 2024/06/09 15:45:10 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <sys/time.h>
#include <string.h>
#include <stdio.h>

static void 	_init_mutex(t_data *ev_thing)
{
	static t_mutex_simul	simul;
	static t_mutex_start	start;
	
	if (pthread_mutex_init(&simul.mutex, NULL) != 0)
		_exit_failure(NULL, "error: Mutex Init fail\n");
	simul.simul = ON;
	ev_thing->simul = &simul;
	if (pthread_mutex_init(&start.mutex, NULL) != 0)
		_exit_failure(NULL, "error: Mutex Init fail\n");
	ev_thing->start = &start;
}

static void	_init_argument(t_ref *args, char **av, int ac)
{
	int	temp[5];
	int	i;

	i = 0;
	memset(temp, -1, 4);
	while (i < ac - 1)
	{
		temp[i] = _atoi(av[i + 1]);
		if (temp[i] == -1)
			_exit_failure(NULL, "Error : Invalid argument\n");
		++i;
	}
	args->philos = temp[0];
	args->time_to_die = temp[1];
	args->time_to_eat = temp[2];
	args->time_to_sleep = temp[3];
	if (temp[4] != -1)
		args->max_time_eat = temp[4];
}

static void	_philo_exec(t_data *ev_thing, pthread_t *threads)
{
	t_philo	*philo;
	int		i;
	
	i = 0;
	philo = ev_thing->head;
	pthread_mutex_lock(&ev_thing->start->mutex);
	while (i < ev_thing->args->philos)
	{
		if (pthread_create(&threads[i], NULL, _routine, philo) != 0)
			_exit_failure(ev_thing, "Pthread failed\n");
		philo = philo->next;
		++i;
	}
	pthread_mutex_unlock(&ev_thing->start->mutex);
	i = 0;
	while (i < ev_thing->args->philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	pthread_t		*threads;
	t_data			ev_thing;
	t_ref			args;
	
	if (ac < 5 || ac > 6)
		_exit_failure(NULL, "error : Incorrect number of arguments\n");
	_init_argument(&args, av, ac);
	_init_mutex(&ev_thing);
	threads = malloc(sizeof(pthread_t) * (args.philos));
	if (!threads)
		return (-1);
	ev_thing.head = _init_philos(&ev_thing, &args);
	if (!ev_thing.head)
		return (free(threads), -1);
	ev_thing.threads = threads;
	ev_thing.args = &args;
	_philo_exec(&ev_thing, threads);
}
