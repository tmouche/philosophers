/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:44:55 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/12 18:09:34 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define M_SEC 1000
# include <stddef.h>
# include <unistd.h>
# include <pthread.h>


typedef	struct s_mutex_data
{
	char			data;
	pthread_mutex_t	mutex;
}				t_mutex_data;

typedef struct s_base
{
	size_t		philos;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		max_time_eat;
}				t_base;

typedef struct s_philo
{
	t_mutex_data	*status;
	size_t			rank;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_eaten;
	size_t			ref_philos;
	size_t			ref_t_to_die;
	size_t			ref_t_to_eat;
	size_t			ref_t_to_sleep;
	size_t			ref_mt_eat;
	struct s_philo	*prev;
	struct s_philo	*next;
}				t_philo;

ssize_t	_atoi(char *str);

int		_lstsize(t_philo *lst);
t_philo	*_lstlast(t_philo *lst);
t_philo	*_lstnew(t_base *ref, int number);
int		_lstadd_back(t_philo **lst, t_philo *new);
void	_lstclear(t_philo **lst);
void	*_routine(void *args);

#endif