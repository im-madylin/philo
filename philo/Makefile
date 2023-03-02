# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/02 13:41:52 by hahlee            #+#    #+#              #
#    Updated: 2023/03/02 20:44:19 by hahlee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CFLAGS	= -g3 -Wall -Wextra -Werror

OUTDIR	= out/
SRCS	= philo.c	init_struct.c	do_action.c	check_state.c	utils.c
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