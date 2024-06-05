/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:35:50 by thibaud           #+#    #+#             */
/*   Updated: 2024/06/04 23:32:48 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"

void	_init_philo_status(t_philo *temp, int name)
{
	if (name % 2 != 0 && temp->next->name != 1)
	{
		pthread_mutex_lock(temp->fork);
		printf("%d %d has taken a fork\n", 0, temp->name);
		printf("%d %d has taken a fork\n", 0, temp->name);
		printf("%d %d is eating\n", 0, philo->rank);
	}
	else
		printf("%d %d is thinking\n", 0, temp->name);
}

t_philo	*_init_philos(t_data *ev_thing, t_ref *args)
{
	t_philo	*temp;
	t_philo	*temp_last;
	int 	i;
	
	temp = _lstnew(args, i);
	if (!temp)
		exit (EXIT_FAILURE);
	ev_thing->head = temp;
	temp_last = temp;
	i = 1;
	while (i <= args->philos)
	{
		temp = _lstnew(args, i);
		if (!temp)
			_lstclear();
		_init_philo_status(temp, i);
		_lstadd_back(temp_last, temp);
		if (pthread_mutex_init(&temp->fork->mutex, NULL) != 0)
			_lstclear();
		++i;
	}
	return (philo);
}