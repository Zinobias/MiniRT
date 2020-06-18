/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   practice.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 15:57:48 by zgargasc       #+#    #+#                */
/*   Updated: 2020/03/05 19:17:05 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "minirt.h"

int		main(void)
{
	void	*mlx;
	void	*mlx_w;
	t_data	img;

	mlx = mlx_init();
	if (!mlx)
		exit(1);
	img.img = mlx_new_image(mlx, 1920, 1080);
	if (!mlx || !img.img)
		exit(1);
	// 				mlx_ptr, x, y, title
	mlx_w = mlx_new_window(mlx, 1920, 1080, "hello worlddd");
	if (!mlx || !mlx_w)
		exit(1);
	// img.addr = mlx_get_data_addr(mlx, &img.bits_p_p, &img.line_l, &img.endian);
	mlx_pixel_put(&img, &mlx_w, 1920/2, 1080/2, rgba(255, 0, 0, 255));
	// for (int i = 50; i < 200; i++) {
	// 	for (int j = 50; j < 200; j++) {
	// 		mlx_pixel_put(&img, &mlx_w, i, j, rgba(255, 0, 0, 255));
	// 	}
	// }
 	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	// mlx_put_image_to_window(mlx, mlx_w, img.img, 0, 0);
	mlx_loop(mlx);
	// int	mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);
	// /*
	// **  origin for x & y is top left corner of the window
	// **  y down is positive
	// **  color is 0x AA RR GG BB format
	// **  x and y must fit into the size of the window, no control is done on the values
	// */
	// char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel,
	// 		   int *size_line, int *endian);
	// /*
	// **  endian : 0 = graphical sever is little endian, 1 = big endian
	// **  usefull in a network environment where graphical app show on a remote monitor that can have a different endian
	// */
	// int	mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr,
	// 			int x, int y);
	// unsigned int	mlx_get_color_value(void *mlx_ptr, int color);
	return (0);
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_l + x * (data->bits_p_p / 8));
    *(unsigned int*)dst = color;
}
