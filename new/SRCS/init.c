/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:35:50 by thibaud           #+#    #+#             */
/*   Updated: 2024/06/06 19:52:16 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"

void	_init_philo_status(t_philo *philo, int name)
{
	if (name % 2 != 0 && philo->next->name != 1)
	{
		pthread_mutex_lock(&philo->fork->mutex);
		philo->fork->data = TAKEN;
		pthread_mutex_unlock(&philo->fork->mutex);
		printf("%d %d has taken a fork\n", 0, philo->name);
		pthread_mutex_lock(&philo->next->fork->mutex);
		philo->next->fork->data = TAKEN;
		pthread_mutex_unlock(&philo->next->fork->mutex);
		printf("%d %d has taken a fork\n", 0, philo->name);
		philo->state = EATING;
		printf("%d %d is eating\n", 0, philo->name);
	}
	else
	{
		philo->state = THINKING;
		printf("%d %d is thinking\n", 0, philo->name);
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
		_init_philo_status(temp, i);
		if (temp_last)
			temp_last->next = temp;
		temp->prev = temp_last;
		if (pthread_mutex_init(&temp->fork->mutex, NULL) != 0)
			return (/*_lstclear(), */NULL);
		++i;
	}
	while (temp_last && temp_last->prev)
		temp_last = temp_last->prev;
	ev_thing = temp_last;
	temp->next = ev_thing->head;
	ev_thing->head->prev = temp;
	return (ev_thing->head);
}