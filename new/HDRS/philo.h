/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche < tmouche@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 02:08:13 by thibaud           #+#    #+#             */
/*   Updated: 2024/06/07 03:16:51 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define M_SEC 1000
# include <stdlib.h>
# include <pthread.h>

typedef enum	e_end
{
	ON,
	OFF
}				t_end;

typedef enum	e_fstate
{
	TAKEN,
	FREE
}				t_fstate;

typedef enum	e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}				t_state;

typedef	struct s_mutex_simul
{
	t_end			simul;
	pthread_mutex_t	mutex;
}				t_mutex_simul;

typedef	struct s_mutex_data
{
	t_fstate		data;
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

typedef struct s_philo
{
	t_mutex_data	*fork;
	int				name;
	t_state			state;
	int				fhand;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_eaten;
	t_ref			*args;
	struct s_data	*ev_things;
	struct s_philo	*prev;
	struct s_philo	*next;
}				t_philo;

typedef struct s_data
{
	t_ref			*args;
	t_philo			*head;
	pthread_t		*threads;
	t_mutex_simul	*simul;
}				t_data;

ssize_t	_atoi(char *str);
size_t	ft_strlen(const char *s, char c);
void	_exit_failure(t_data *args, char *str);
t_philo	*_init_philos(t_data *ev_thing, t_ref *args);

t_philo	*_lstnew(t_ref *args, int number);
void	*_routine(void *args);

#endif