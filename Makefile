# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/02 13:41:52 by hahlee            #+#    #+#              #
#    Updated: 2023/03/02 13:57:04 by hahlee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
# BONUS_NAME = checker
CFLAGS	= -Wall -Wextra -Werror

OUTDIR	= out/
MANDATORY_OUTDIR = out/philo
# BONUS_OUTDIR = out/push_swap_bonus
SRCS	= philo/philo.c philo/utils.c philo/init_struct.c
# BONUS_SRCS	= push_swap_bonus/checker_bonus.c push_swap_bonus/change_stack_bonus.c push_swap_bonus/stack_command_bonus.c push_swap_bonus/stack_command2_bonus.c push_swap_bonus/stack_command3_bonus.c push_swap_bonus/check_argu_bonus.c push_swap_bonus/check_command_bonus.c
OBJS	= $(SRCS:%.c=$(OUTDIR)%.o)
# BONUS_OBJS = $(BONUS_SRCS:%.c=$(OUTDIR)%.o)

all : $(NAME)

# bonus : $(BONUS_NAME)

$(OUTDIR):
	mkdir $@

# ifeq (, $(findstring bonus, $(MAKECMDGOALS)))
$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
$(MANDATORY_OUTDIR):
	mkdir $@
# else
# $(BONUS_NAME) : $(BONUS_OBJS) $(GNL_OBJS)
# 	$(MAKE) -j -C libft
# 	$(CC) $(CFLAGS) $(BONUS_OBJS) $(GNL_OBJS) -o $@ $(LDFLAGS)
# $(BONUS_OUTDIR):
# 	mkdir $@
# $(GNL_OUTDIR):
# 	mkdir $@
# endif

clean :
		$(RM) -r $(OUTDIR)

fclean : clean
		# $(RM) -r $(NAME)
# fclean : clean
# 		$(RM) -r $(NAME) $(BONUS_NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

# bre :
# 	$(MAKE) fclean
# 	$(MAKE) bonus

$(OBJS): $(OUTDIR)%.o: %.c | $(OUTDIR) $(MANDATORY_OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# $(BONUS_OBJS): $(OUTDIR)%.o: %.c | $(OUTDIR) $(BONUS_OUTDIR)
# 	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : all bonus clean fclean re bre philo