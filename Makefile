# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeredit <mmeredit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 20:27:18 by fdarkhaw          #+#    #+#              #
#    Updated: 2022/08/26 15:34:28 by mmeredit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	cub3D
SRCS_DIR	= 	src/
OBJS_DIR	= 	obj/
INCS_DIR	= 	include
SRCS_F		= 	main.c	parser_0.c		error.c		get_next_line.c \
				get_next_line_utils.c	cleaner.c execute.c \
				parser_1.c	parser_2.c	parser_3.c	print_utils.c	\
				draw.c	init_execute_info.c	button_execute.c

SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_F))
OBJS_F		= $(patsubst %.c, %.o, $(SRCS_F))
DEPS_F		= $(patsubst %.c, %.d, $(SRCS_F))
OBJS		= $(addprefix $(OBJS_DIR), $(OBJS_F))
DEPS		= $(addprefix $(OBJS_DIR), $(DEPS_F))

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -MMD -O2
FSA			= -fsanitize=address -g
LFLAGS		= -Llibft -lft
LIB			= libft.a
LIB_DIR		= libft/
MLX_DIR		= mlx/
MLX			= libmlx.a

all: $(NAME)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
		$(CC) $(CFLAGS) -I$(INCS_DIR) -I$(MLX_DIR) -c $< -o $@

$(OBJS_DIR) :
		mkdir -p $@

$(NAME):  $(OBJS_DIR) $(OBJS) $(LIB_DIR)$(LIB) $(MLX_DIR)$(MLX) Makefile
		$(CC) $(CFLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit $(OBJS) $(LFLAGS) -o $@

$(LIB_DIR)$(LIB) : ;
		make -C $(LIB_DIR)

$(MLX_DIR)$(MLX) : ;
		make -C $(MLX_DIR)

clean :
	rm -rf $(OBJS_DIR)
	make clean -C $(LIB_DIR)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIB_DIR)
	make clean -C $(MLX_DIR)

re: fclean all

.PHONY:
		all clean fclean re

-include $(DEPS)
