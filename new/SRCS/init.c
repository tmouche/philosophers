/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:35:50 by thibaud           #+#    #+#             */
/*   Updated: 2024/06/08 17:45:42 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <stdio.h>

void	_init_philo_status(t_philo **philo)
{
	t_philo	*head;

	head = *(philo);
	head->fork->data = TAKEN;
	printf("%d %d has taken a fork\n", 0, head->name);
	head->next->fork->data = TAKEN;
	printf("%d %d has taken a fork\n", 0, head->name);
	head->state = EATING;
	printf("%d %d is eating\n", 0, head->name);
	head = head->next;
	while (head->name != 1)
	{
		if (head->name % 2 != 0 && head->next->name != 1)
		{
			head->fork->data = TAKEN;
			printf("%d %d has taken a fork\n", 0, head->name);
			head->next->fork->data = TAKEN;
			printf("%d %d has taken a fork\n", 0, head->name);
			head->state = EATING;
			printf("%d %d is eating\n", 0, head->name);
		}
		else
		{
			head->state = THINKING;
			printf("%d %d is thinking\n", 0, head->name);
		}
		head = head->next;
	}
}

t_philo	*_init_philos(t_data *ev_thing, t_ref *args)
{
	t_philo	*temp;
	t_philo	*temp_last;
	int 	i;
	
	temp = NULL;
	i = 1;
	while (i <= args->philos)
	{
		temp_last = temp;
		temp = _lstnew(args, i);
		if (!temp)
			return (/*_lstclear(), */NULL);
		temp->ev_things = ev_thing;
		if (temp_last)
			temp_last->next = temp;
		temp->prev = temp_last;
		if (pthread_mutex_init(&temp->fork->mutex, NULL) != 0)
			return (/*_lstclear(), */NULL);
		++i;
	}
	while (temp_last && temp_last->prev)
		temp_last = temp_last->prev;
	ev_thing->head = temp_last;
	temp->next = ev_thing->head;
	ev_thing->head->prev = temp;
	_init_philo_status(&ev_thing->head);
	return (ev_thing->head);
}