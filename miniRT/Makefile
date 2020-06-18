# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: zgargasc <zgargasc@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/14 16:37:58 by zgargasc       #+#    #+#                 #
#    Updated: 2020/03/05 19:05:18 by zgargasc      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := MiniRT

SRC := practice.c

MLX_PATH := ./mlx/

MLX := libmlx.dylib

INC := minirt.h

CFLAGS := -Wall -Wextra -Werror -I.

LXFLAGS := -Lmlx/ -lmlx -framework OpenGL -framework AppKit

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(MLX) $(OBJ)
	@printf "\e[1;34mCompiling Project\n\e[0m"
	@$(CC) $(LXFLAGS) $(CFLAGS) -o $(NAME) $(OBJ)

$(MLX):
	@printf "\e[1;34mCompiling MLX\e[0m"
	@$(MAKE) -C $(MLX_PATH)
	@printf "Moving Dylib"
	@mv mlx/$(MLX) .

%.o: %.c
	@printf "\e[1;34mCompiling Object files\n\e[0m"
	@gcc -Wall -Wextra -Werror -Imlx -Iinc -Ilibft -c $< -o $@

clean:
	@printf "\e[1;34mMaking clean\n\e[0m"
	@$(RM) $(OBJ)
	@$(MAKE) -C $(MLX_PATH) clean

fclean: clean
	@$(RM) $(MLX) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
