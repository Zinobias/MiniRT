
NAME := minirt

SRC := GNL/get_next_line_bonus.c GNL/get_next_line_utils_bonus.c \
./libftish/atod.c ./colors/color_structs.c ./colors/colors.c ./bmp/get_pixel.c \
./hooks/hooks.c ./IMG_list/img_list.c ./inter_objects/intersect.c \
./inter_objects/intersect_cylinder.c ./inter_objects/intersect_plane.c \
./inter_objects/intersect_sphere.c ./inter_objects/intersect_square.c \
./inter_objects/intersect_triangle.c ./lighting/lighting.c \
./Light_list/lights_list.c ./bmp/make_bmp.c \
minirt.c ./Raytracing/mlx_start.c ./Obj_functions/obj_functions1.c \
./Obj_functions/object_functions2.c ./parser/parser.c ./parser/parser_utils.c \
./parser/parser_utils2.c ./Math/quad_solve.c ./Raytracing/raytracer.c \
./parser/utils.c ./Vector_functions/vector_lib.c \
./Vector_functions/vector_lib2.c ./Vector_functions/vector_lib3.c \
./Raytracing/look_at.c ./parser/list_utils.c \
./libftish/ft_calloc.c \

MLX_PATH := ./mlx/

MLX := libmlx.dylib

INC := minirt.h

CFLAGS := -fsanitize=address -Wall -Wextra -Werror -I.

LXFLAGS := -Lmlx/ -Lmlx -framework OpenGL -framework AppKit

OBJ := $(SRC:.c=.o)

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
