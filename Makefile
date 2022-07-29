# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 20:27:18 by fdarkhaw          #+#    #+#              #
#    Updated: 2022/07/29 21:09:39 by fdarkhaw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	cub3D
SRCS_DIR	= 	src/
OBJS_DIR	= 	obj/
INCS_DIR	= 	include
SRCS_F		= 	main.c	parser.c		error.c		get_next_line.c \
				get_next_line_utils.c	cleane.c

SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_F))
OBJS_F		= $(patsubst %.c, %.o, $(SRCS_F))
DEPS_F		= $(patsubst %.c, %.d, $(SRCS_F))
OBJS		= $(addprefix $(OBJS_DIR), $(OBJS_F))
DEPS		= $(addprefix $(OBJS_DIR), $(DEPS_F))

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -MMD -O2
LFLAGS		= -Llibft -lft
LIB			= libft.a
LIB_DIR		= libft/

all: $(NAME)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
		$(CC) $(CFLAGS) -I$(INCS_DIR) -c $< -o $@

$(OBJS_DIR) :
		mkdir -p $@

$(NAME):  $(OBJS_DIR) $(OBJS) $(LIB_DIR)$(LIB) Makefile
		$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $@

$(LIB_DIR)$(LIB) : ;
		make -C $(LIB_DIR)

clean :
	rm -rf $(OBJS_DIR)
	make clean -C $(LIB_DIR)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIB_DIR)

re: fclean all

.PHONY:
		all clean fclean re

-include $(DEPS)
