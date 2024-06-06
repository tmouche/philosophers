/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 02:02:42 by thibaud           #+#    #+#             */
/*   Updated: 2024/06/06 19:59:58 by tmouche          ###   ########.fr       */
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

void	_philo_exec(t_data *ev_thing, pthread_t *threads)
{
	t_philo	*philo;
	int		i;
	
	i = 0;
	while (i < ev_thing->args->philos)
	{
		if (pthread_create(&threads[i], NULL, _routine, philo) != 0)
			_exit_failure(ev_thing, "Pthread failed\n");
		philo = philo->next;
		++i;
	}
	i = 0;
	while (i < ev_thing->args->philos + 1)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_mutex_simul	simul;
	pthread_t		*threads;
	t_data			ev_thing;
	t_ref			args;
	
	if (ac < 5 || ac > 6)
		_exit_failure(NULL, "error : Incorrect number of arguments\n");
	_init_argument(&args, av, ac);
	if (pthread_mutex_init(&simul.mutex, NULL) != 0)
		_exit_failure(NULL, "error: Mutex Init fail\n");
	simul.simul = ON;
	ev_thing.simul = &simul;
	threads = malloc(sizeof(pthread_t) * (args.philos));
	if (!threads)
		return (-1);
	ev_thing.head = _init_philos(&ev_thing, &args);
	if (!ev_thing.head)
		return (free(threads), -1);
	ev_thing.threads = threads;
	ev_thing.args = &args;
	_philo_exec();
}
