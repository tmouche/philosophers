/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:33:19 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/14 14:37:40 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <stdlib.h>

t_philo	*_lstnew(t_base *ref, int number)
{
	t_philo			*new;
	t_mutex_data	*mutex;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	mutex = malloc(sizeof(t_mutex_data));
	if (!mutex)
		return (NULL);
	new->fork = mutex;
	new->rank = number;
	new->time_eaten = 0;
	new->time_to_die = 0;
	new->time_to_eat = 0;
	new->time_to_sleep = 0;
	new->ref = ref;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_philo	*_lstlast(t_philo *lst)
{
	while (lst->rank != 1)
		lst = lst->next;
	lst = lst->prev;
	return (lst);
}

int	_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*lst_temp;

	if (*lst)
	{
		lst_temp = _lstlast(*lst);
		lst_temp->next = new;
		new->prev = lst_temp;
		new->next = *lst;
		(*lst)->prev = new;
	}
	else
	{
		*lst = new;
		new->next = new;
		new->prev = new;
	}
	return (0);
}

void	_lstclear(t_philo **lst)
{
	t_philo	*temp;

	if (!lst)
		return ;
	temp = *lst;
	while (*lst)
	{
		temp = temp->next;
		pthread_mutex_destroy(&temp->fork->mutex);
		free(temp->fork);
		free(*lst);
		*lst = temp;
	}
	exit (EXIT_FAILURE);
}