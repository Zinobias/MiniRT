# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: zgargasc <zgargasc@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/14 16:37:58 by zgargasc      #+#    #+#                  #
#    Updated: 2020/06/20 17:11:18 by zgargasc      ########   odam.nl          #
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

test:
	@printf "\e[1;34mMaking test\n\e[0m"
	@gcc -g atod.c minirt.c obj_functions1.c parser_utils.c colors.c parser.c utils.c ./GNL/*.c
	@./a.out
	
testc:
	@printf "\e[1;34mMaking clean\n\e[0m"
	@$(RM) -f ./a.out
	@$(RM) -r ./a.out.dSYM

make testr: testc test

git:
	@printf "\e[1;34mAdding\n\e[0m"
	@git add *
	@git commit -m "yahr"
	@printf "\e[1;34mCommit\n\e[0m"
	@git push
	@printf "\e[1;34mPushed\n\e[0m"

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
