# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmouche < tmouche@student.42lyon.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 10:53:51 by tmouche           #+#    #+#              #
#    Updated: 2024/06/11 16:55:52 by tmouche          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HDRS	:= philo.h

SRCS	:=	main.c utils.c chained_list_utils1.c routine.c routine_action.c init.c

SRCS_D	:= SRCS/
HDRS_D	:= HDRS/
OBJS_D	:= OBJS/

CFLAGS	:= -Wall -Wextra -Werror -g -pthread
CC		:= cc
AR		:= ar rcs
RM		:= rm -rf

NAME	:= philo	
OBJS	:= $(SRCS:%.c=$(OBJS_D)%.o)

all: $(NAME) 

$(NAME): $(OBJS_D) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


$(OBJS_D)%.o: $(SRCS_D)%.c $(HDRS:%=$(HDRS_D)%) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_D):
	@mkdir -p $(OBJS_D)

clean:
	$(RM) -r $(OBJS_D)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
