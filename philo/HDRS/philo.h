/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:44:55 by tmouche           #+#    #+#             */
/*   Updated: 2024/03/14 16:23:12 by tmouche          ###   ########.fr       */
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
	int				*data;
	pthread_mutex_t	mutex;
}				t_mutex_data;

typedef struct s_clocker
{
	int		m_sec;
	int		sec;
}				t_clocker;

typedef	struct s_state
{
	int	*eat;
	int	*sleep;
	int	*think;
	int	*fork_taken;
	int	*fork_free;
}				t_state;

typedef struct s_base
{
	int		philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		max_time_eat;
}				t_base;

typedef struct s_philo
{
	t_mutex_data	*fork;
	int				*status;
	int				rank;
	int				fork_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_eaten;
	t_base			*ref;
	t_state			*state;
	t_clocker		*clocker;
	struct s_philo	*prev;
	struct s_philo	*next;
}				t_philo;

ssize_t	_atoi(char *str);
void	_init_state(t_state *state);

t_philo	*_lstlast(t_philo *lst);
t_philo	*_lstnew(t_base *ref, int number);
int		_lstadd_back(t_philo **lst, t_philo *new);
void	_lstclear(t_philo **lst);
void	*_routine(void *args);
void	*_clocker(void *args)

#endif