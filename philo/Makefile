# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/02 13:41:52 by hahlee            #+#    #+#              #
#    Updated: 2023/03/15 17:00:00 by hahlee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CFLAGS	= -g3 -Wall -Wextra -Werror -fsanitize=thread

OUTDIR	= out/
SRCS	= philo.c	init_struct.c	do_action.c	do_action2.c	check_state.c	utils.c
OBJS	= $(SRCS:%.c=$(OUTDIR)%.o)

all : $(NAME)

$(OUTDIR):
	mkdir $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean :
		$(RM) -r $(OUTDIR)

fclean : clean
		$(RM) -r $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

$(OBJS): $(OUTDIR)%.o: %.c | $(OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : all bonus clean fclean re