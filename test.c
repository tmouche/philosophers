/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 22:43:48 by thibaud           #+#    #+#             */
/*   Updated: 2024/06/06 19:25:32 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <strings.h>
#include <stdlib.h>
#include <pthread.h>

typedef	struct s_mutex_print
{
	int				print;
	pthread_mutex_t	mutex;
}				t_mutex_print;

typedef	struct s_mutex_data
{
	int				data;
	pthread_mutex_t	mutex;
}				t_mutex_data;

typedef	struct s_args
{
	t_mutex_data 	*mutex;
	t_mutex_print	*mutex_print;
	pthread_t		*thread;
	pthread_t		*thread2;
}				t_args;

void	printer(char *to_print)
{
	printf("%s", to_print);
}

void	*fct_test1(void *args)
{
	t_args	*ptr;
	
	ptr = args;
	pthread_mutex_lock(&ptr->mutex->mutex);
	printer("1 prelock\n");
	printer("1 postlock\n");
	pthread_mutex_unlock(&ptr->mutex->mutex);
	return (NULL);
}

void	*fct_test2(void *args)
{
	t_args	*ptr;
	int		i = 0;
	
	ptr = args;
	while (i < 100000)
		++i;
	ptr->mutex->data = 2;
	printf("%d\n", ptr->mutex->data);
	if (ptr->mutex->data == 2)
		pthread_mutex_lock(&ptr->mutex->mutex);
	else
	{
		printf("ok\n");
		return (NULL);
	}
	printer("2 prelock\n");
	printer("2 postlock\n");
	pthread_mutex_unlock(&ptr->mutex->mutex);
	return (NULL);
}

int main(void)
{
	t_args			glob;
    t_mutex_data	test;
	t_mutex_print	print;
	pthread_t		thread;
	pthread_t		thread2;
	
	glob.mutex = &test;
	glob.mutex_print = &print;
	test.data = 0;
	pthread_mutex_init(&glob.mutex->mutex, NULL);
	pthread_mutex_init(&glob.mutex_print->mutex, NULL);
	pthread_create(&thread, NULL, fct_test1, &glob);
	pthread_create(&thread2, NULL, fct_test2, &glob);
	pthread_join(thread, NULL);
	pthread_join(thread2, NULL);
	printf("end\n");
	return (1);
}
