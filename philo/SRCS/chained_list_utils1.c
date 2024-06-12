/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:33:19 by tmouche           #+#    #+#             */
/*   Updated: 2024/06/12 11:13:23 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <stdlib.h>
#include <stdio.h>

t_philo	*_lstnew(t_ref *args, int number)
{
	t_philo			*new;
	t_mutex_data	*data;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	data = malloc(sizeof(t_mutex_data));
	if (!data)
		return (free(new), NULL);
	new->fork = data;
	new->fork->data = FREE;
	new->name = number;
	new->time_eaten = 0;
	new->time_to_die = 0;
	new->time_to_eat = 0;
	new->time_to_sleep = 0;
	new->fhand = 0;
	new->args = args;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	_lstclear(t_philo *lst, t_end state)
{
	t_philo	*temp;

	if (state == OFF)
	{
		if (lst->prev != lst)
			lst->prev->next = NULL;
		else
			lst->next = NULL;
	}
	temp = lst;
	while (lst)
	{
		temp = temp->next;
		pthread_mutex_destroy(&lst->fork->mutex);
		free(lst->fork);
		free(lst);
		lst = temp;
	}
}
