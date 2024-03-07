/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:44:55 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/07 16:24:36 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stddef.h>
# include <unistd.h>

typedef struct s_base
{
	ssize_t				philos;
	ssize_t				time_to_die;
	ssize_t				time_to_eat;
	ssize_t				time_to_sleep;
	ssize_t				max_time_eat;
}				t_base;

typedef struct s_philo
{
	size_t			rank;
	char			status;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_eaten;
	struct s_philo	*prev;
	struct s_philo	*next;
}				t_philo;

ssize_t	_atoi(char *str);

int		_lstsize(t_philo *lst);
t_philo	*_lstlast(t_philo *lst);
t_philo	*_lstnew(t_base *ref, int number);
int		_lstadd_back(t_philo **lst, t_philo *new);
void	_lstclear(t_philo **lst);

#endif