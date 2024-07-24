
NAME = trace

SRCS = main utils1 draw caster\
		./getnextline/get_next_line ./getnextline/get_next_line_utils \
		./libft/ft_strdup ./libft/ft_memcpy \

CC = cc
CCFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

MILIB = -I /usr/X11/include -g -L /usr/X11/lib -l minilibx -framework OpenGL -framework AppKit

MLX_LIB_DIR = minilibx-linux/
MLX_INCLUDE = -I minilibx-linux/

INC = -Iincludes -I/usr/include -Imlx_linux

LMLX_FLAGS = -L$(MLX_LIB_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -fPIC


all: $(NAME)

$(NAME): $(SRCS:=.o)
	make -s -C minilibx-linux/
	$(CC) $(CCFLAGS) $(SRCS:=.o) $(INC) $(LMLX_FLAGS) $(MLX_INCLUDE) -o $(NAME)
	@echo "\e[0;32m Project \e[1;36m$(NAME)\e[0;32m compiled successfully\e[0m"

clean:
	rm -fr $(SRCS:=.o)
#	make clean -s -C minilibx-linux/
	@echo "\e[0;31m Removed object files.\e[0m"

fclean: clean
	rm -fr $(NAME)
	@echo "\e[0;31m Removed executable \e[1;36m$(NAME)\e[0;31m.\e[0m"

re: fclean $(NAME)

rec: re
	make -s clean
	clear

.PHONY: all clean fclean re rec