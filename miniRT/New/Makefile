
NAME := minirt

SRC := GNL/get_next_line_bonus.c GNL/get_next_line_utils_bonus.c \
atod.c color_structs.c colors.c get_pixel.c hooks.c img_list.c ./inter_objects/intersect.c \
./inter_objects/intersect_cylinder.c ./inter_objects/intersect_plane.c \
./inter_objects/intersect_sphere.c ./inter_objects/intersect_square.c \
./inter_objects/intersect_triangle.c lighting.c lights_list.c make_bmp.c \
minirt.c mlx_start.c obj_functions1.c object_functions2.c parser.c parser_utils.c \
 parser_utils2.c quad_solve.c raytracer.c utils.c vector_lib.c vector_lib2.c vector_lib3.c \
look_at.c list_utils.c libmlx.dylib \

MLX_PATH := ./mlx/

MLX := libmlx.dylib

INC := minirt.h

CFLAGS := -fsanitize=address -Wall -Wextra -Werror -I.

LXFLAGS := -Lmlx/ -Lmlx -framework OpenGL -framework AppKit

OBJ := $(SRC:.c=.o)

test:
	@printf "\e[1;34mMaking test\n\e[0m"
	@gcc -Wall -Werror -Wextra -I. -Imlx -Iinc -Ilibft -Lmlx/ \
	-Lmlx -framework OpenGL -framework AppKit -g -o MiniRT \
	GNL/get_next_line_bonus.c \
	GNL/get_next_line_utils_bonus.c libmlx.dylib \
	atod.c color_structs.c colors.c get_pixel.c hooks.c img_list.c intersect.c \
	intersect_cylinder.c intersect_plane.c intersect_sphere.c \
	intersect_square.c intersect_triangle.c lighting.c lights_list.c \
	make_bmp.c minirt.c mlx_start.c obj_functions1.c object_functions2.c \
	parser.c parser_utils.c parser_utils2.c \
	quad_solve.c raytracer.c utils.c vector_lib.c vector_lib2.c vector_lib3.c \
	look_at.c list_utils.c
	@./minirt /Users/pani_zino/pani/minirt_new/scene.rt

testc:
	@printf "\e[1;34mMaking clean\n\e[0m"
	@$(RM) -f ./minirt
	@$(RM) -r ./minirt.dSYM

make testr: testc test

git:
	@printf "\e[1;34mAdding\n\e[0m"
	@git add *
	@git commit -m "Automated git"
	@printf "\e[1;34mCommit\n\e[0m"
	@git push
	@printf "\e[1;34mPushed\n\e[0m"

all: $(NAME)

$(NAME): $(MLX) $(OBJ)
	@printf "\e[1;34mCompiling Project\n\e[0m"
	@$(CC) $(CFLAGS) $(LXFLAGS) -g -o $(NAME) $(OBJ) $(MLX)

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
	@$(RM) get_next_line_bonus.o get_next_line_utils_bonus.o
	@$(MAKE) -C $(MLX_PATH) clean

fclean: clean
	@$(RM) $(MLX) $(NAME) $(NAME).h.gch

re: fclean all

.PHONY: all clean fclean re bonus
