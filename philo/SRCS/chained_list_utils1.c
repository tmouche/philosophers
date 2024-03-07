/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:33:19 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/07 16:23:29 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <stdlib.h>

t_philo	*_lstnew(t_base *ref, int number)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->rank = number;
	new->status = 's';
	new->time_eaten = 0;
	new->time_to_die = (size_t)ref->time_to_die;
	new->time_to_eat = (size_t)ref->time_to_eat;
	new->time_to_sleep = (size_t)ref->time_to_sleep;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	_lstsize(t_philo *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_philo	*_lstlast(t_philo *lst)
{
	while (lst->next)
		lst = lst->next;
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
	}
	else
		*lst = new;
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