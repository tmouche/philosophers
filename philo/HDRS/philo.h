/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 02:08:13 by thibaud           #+#    #+#             */
/*   Updated: 2024/06/12 11:09:27 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define M_SEC 1000
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

typedef enum e_end
{
	ON,
	OFF,
	CONTINUE
}				t_end;

typedef enum e_fstate
{
	TAKEN,
	FREE
}				t_fstate;

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}				t_state;

typedef struct s_mutux_start
{
	pthread_mutex_t	mutex;
}				t_mutex_start;

typedef struct s_mutex_simul
{
	int				simul;
	pthread_mutex_t	mutex;
}				t_mutex_simul;

typedef struct s_mutex_data
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
	t_mutex_start	*start;
}				t_data;

ssize_t	_atoi(char *str);
size_t	ft_strlen(const char *s, char c);
t_philo	*_lstnew(t_ref *args, int number);
void	_lstclear(t_philo *lst, t_end state);

t_philo	*_init_philos(t_data *ev_thing, t_ref *args);
void	_exit_end(t_data *ev_thing, char *str, t_end last);

t_end	_eating(t_philo *philo, size_t *timer, int act_time);
t_end	_sleeping(t_philo *philo, size_t *timer);
t_end	_thinking(t_philo *philo, size_t *timer);
t_end	_printer(t_philo *philo, size_t *timer, char *str);
void	*_routine(void *args);

#endif