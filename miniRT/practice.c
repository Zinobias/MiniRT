/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   practice.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 15:57:48 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/06/20 17:08:02 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "minirt.h"

int	close_window_esc(int keycode, t_data *mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return (0);
}

int		close_win_x(t_data *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
}

int		main(void)
{
	t_data	mlx;

	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		error(MLX);
	mlx.img = mlx_new_image(mlx.mlx, 1920, 1080);
	if (!mlx.mlx || !mlx.img)
		error(MLX);
	// 				mlx_ptr, x, y, title
	mlx.win = mlx_new_window(mlx.mlx, 1920, 1080, "hello worlddd");
	if (!mlx.mlx || !mlx.win)
		error(MLX);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_p_p, &mlx.line_l, &mlx.endian);
	mlx_pixel_put(&mlx, &mlx.win, 1920/2, 1080/2, rgba(255, 5, 10, 255));
	// for (int i = 50; i < 200; i++) {
	// 	for (int j = 50; j < 200; j++) {
	// 		mlx_pixel_put(&img, &mlx_w, i, j, rgba(255, 0, 0, 255));
	// 	}
	// }
 	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	// mlx_put_image_to_window(mlx, mlx_w, img.img, 0, 0);
	mlx_loop(mlx.mlx);
	mlx_key_hook(&mlx.win, close_window_esc, &mlx);
	mlx_hook(mlx.win, , 0, close_win_x, &mlx);
	// escape = 53
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

void            my_mlx_pixel_put(t_data *mlx, int x, int y, int color)
{
    char    *dst;

    dst = mlx->addr + (y * mlx->line_l + x * (mlx->bits_p_p / 8));
    *(unsigned int*)dst = color;
}
