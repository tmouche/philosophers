/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:35:50 by thibaud           #+#    #+#             */
/*   Updated: 2024/06/04 00:47:20 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../HDRS/philo.h"

t_philo	*_init_philos(t_data *ev_thing, t_ref *args)
{
	t_philo	*temp;
	int 	i;
	
	i = 0;
	while (i <= args->philos)
	{
		temp = _lstnew(args, i);
		if (!temp)
			_lstclear(philo);
		_lstadd_back(philo, temp);
		if (pthread_mutex_init(&temp->fork->mutex, NULL) != 0)
			_lstclear(philo);
		_init_philo_status(state, temp);
		++i;
	}
	return (philo);
}