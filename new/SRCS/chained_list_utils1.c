/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:33:19 by tmouche           #+#    #+#             */
/*   Updated: 2024/06/10 17:02:01 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <stdlib.h>

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

void	_lstclear(t_philo *lst, int	stop)
{
	t_philo	*temp;

	if (!lst)
		return ;
	temp = lst;
	while (lst)
	{
		temp = temp->prev;
		if (stop == 1)
			pthread_mutex_destroy(&temp->fork->mutex);
		free(temp->fork);
		free(lst);
		lst = temp;
	}
}