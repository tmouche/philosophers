/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 02:08:13 by thibaud           #+#    #+#             */
/*   Updated: 2024/06/03 19:04:24 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#define M_SEC 1000
#include <stdlib.h>
#include <pthread.h>

typedef	struct s_mutex_data
{
	int				*data;
	pthread_mutex_t	mutex;
}				t_mutex_data;

typedef struct s_ref
{
	int		philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		max_time_eat;
}				t_ref;

typedef struct s_data
{
	int	time;
}				t_data;

typedef struct s_philo
{
	t_mutex_data	*fork;
	int				name;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_eaten;
	t_ref			*args;
	t_data			*ev_things;
	struct s_philo	*prev;
	struct s_philo	*next;
}				t_philo;

ssize_t	_atoi(char *str);
size_t	ft_strlen(const char *s, char c);
void	_exit_failure(t_data *args, char *str);

#endif