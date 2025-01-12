/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 21:02:47 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/10/20 15:22:00 by zilisabethp   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		key_input(int keycode, t_data *mlx)
{
	if (keycode == 124)
		cam_next(mlx);
	if (keycode == 123)
		cam_back(mlx);
	if (keycode == 53)
	{
		clear_img_l(mlx);
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return (0);
}

int		close_win_x(t_data *mlx)
{
	clear_img_l(mlx);
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (0);
}

void	cam_next(t_data *mlx)
{
	if (mlx->current_cam->next)
	{
		mlx->current_cam = mlx->current_cam->next;
		mlx_put_image_to_window(mlx->mlx, mlx->win,
			mlx->current_cam->img, 0, 0);
	}
	else
	{
		mlx->current_cam = mlx->img_l;
		mlx_clear_window(mlx->mlx, mlx->win);
		mlx_put_image_to_window(mlx->mlx, mlx->win,
			mlx->current_cam->img, 0, 0);
	}
}

void	cam_back(t_data *mlx)
{
	if (mlx->current_cam->back)
	{
		mlx->current_cam = mlx->current_cam->back;
		mlx_clear_window(mlx->mlx, mlx->win);
		mlx_put_image_to_window(mlx->mlx,
			mlx->win, mlx->current_cam->img, 0, 0);
	}
	else if (mlx->img_tail)
	{
		mlx->current_cam = mlx->img_tail;
		mlx_clear_window(mlx->mlx, mlx->win);
		mlx_put_image_to_window(mlx->mlx,
			mlx->win, mlx->current_cam->img, 0, 0);
	}
}

void	mlx_hooks_(t_data **mlx_)
{
	t_data *mlx;

	mlx = *mlx_;
	mlx->current_cam = mlx->img_l;
	mlx_key_hook(mlx->win, key_input, mlx);
	mlx_hook(mlx->win, 17, 0, close_win_x, mlx);
	mlx_loop(mlx->mlx);
	return ;
}
