/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche < tmouche@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:33:19 by tmouche           #+#    #+#             */
/*   Updated: 2024/06/05 18:22:46 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"
#include <stdlib.h>

t_philo	*_lstnew(t_ref *args, int number)
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
	new->fork->data = 0;
	new->time_eaten = 0;
	new->time_to_die = 0;
	new->time_to_eat = 0;
	new->time_to_sleep = 0;
	new->args = args;
	new->next = NULL;	
	new->prev = NULL;
	return (new);
}

// void	_lstclear(t_philo *lst)
// {
// 	t_philo	*temp;

// 	if (!lst)
// 		return ;
// 	temp = *lst;
// 	while (*lst)
// 	{
// 		temp = temp->next;
// 		pthread_mutex_destroy(&temp->fork->mutex);
// 		free(temp->fork);
// 		free(*lst);
// 		*lst = temp;
// 	}
// 	exit (EXIT_FAILURE);
// }