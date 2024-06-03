/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 02:02:42 by thibaud           #+#    #+#             */
/*   Updated: 2024/06/03 19:01:25 by thibaud          ###   ########.fr       */
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

void	_stopwatch(int time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (time != tv.tv_usec * M_SEC)
		time = tv.tv_usec * M_SEC;
}

int	main(int ac, char **av)
{
	t_data	ev_thing;
	t_ref	args;
	
	if (ac < 5 || ac > 6)
		_exit_failure(NULL, "error : Incorrect number of arguments\n");
	_init_argument(&args, av, ac);
	
}