/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:33:19 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/12 19:13:50 by tmouche          ###   ########.fr       */
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
	new->status = mutex;
	new->rank = number;
	new->time_eaten = 0;
	new->time_to_die = 0;
	new->time_to_eat = 0;
	new->time_to_sleep = 0;
	new->ref_philos = (size_t)ref->philos;
	new->ref_t_to_die = (size_t)ref->time_to_die;
	new->ref_t_to_eat = (size_t)ref->time_to_eat;
	new->ref_t_to_sleep = (size_t)ref->time_to_sleep;
	new->ref_mt_eat = (size_t)ref->max_time_eat;
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
		free(*lst);
		*lst = temp;
	}
	exit (EXIT_FAILURE);
}