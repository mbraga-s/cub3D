# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manumart <manumart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/12 15:38:55 by manumart          #+#    #+#              #
#    Updated: 2024/09/08 18:50:29 by manumart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#$(VERBOSE).SILENT:

NAME =cub3D

SRCS_NAME =	main.c  get_next_line.c get_next_line_utils.c parse.c textures.c \
			 free.c colors.c map.c player.c floodfill.c draw.c caster.c caster_utils.c movement.c init.c\

CC = cc
CFLAGS = -Wall -Werror -Wextra  -g

RM = rm -rf

SRC_PATH = ./

OBJ_PATH = ./objects

LIBFT = ./libft/libft.a
LIBFT_PATH = ./libft

OBJS = $(addprefix $(OBJ_PATH)/, $(SRCS_NAME:.c=.o))

SRC = $(addprefix $(SRC_PATH)/, $(SRCS_NAME))

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
		@echo "\e[0;32m Project \e[1;36m$(NAME)\e[0;32m compiled successfully\e[0m"
		$(CC) $(OBJS) -o $(NAME) $(LIBFT) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c 
		mkdir -p objects
		$(CC)	-c $< -o $@

$(LIBFT):  
	make -s -C $(LIBFT_PATH)

clean:
		make clean -s -C $(LIBFT_PATH)
		@echo "\e[0;31m Removed object files.\e[0m"
		rm -rf $(OBJS)

fclean: clean
		make fclean -s -C $(LIBFT_PATH)
		rmdir objects
		@echo "\e[0;31m Removed executable \e[1;36m$(NAME)\e[0;31m.\e[0m"
		rm -rf $(NAME)

re: fclean $(LIBFT) all

.PHONY: all clean fclean re

# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3D



