/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 15:21:31 by ldideric      #+#    #+#                 */
/*   Updated: 2020/06/27 16:30:50 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

static void			saved_images_hooks(t_vars *vars)
{
	if (vars->data.sav[vars->data.b.i_c] == NULL)
	{
		ft_printf("Rendering...\n");
		px_loop(&vars->data);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
	}
	else
	{
		ft_printf("Loading from cache...\n");
		ft_printf("\x1b[38;5;83m[+]\x1b[0mCam: %02d/%02d\n", vars->data.b.i_c + 1,	vars->data.b.cam.max);
		ft_printf("\x1b[38;5;83m[+]\x1b[0mpos:%d,%d,%d - vec:%d,%d,%d - fov:%d\n---\n", (int)vars->data.b.cam.c[vars->data.b.i_c].pos.x, (int)vars->data.b.cam.c[vars->data.b.i_c].pos.y, (int)vars->data.b.cam.c[vars->data.b.i_c].pos.z, (int)vars->data.b.cam.c[vars->data.b.i_c].vec.x, (int)vars->data.b.cam.c[vars->data.b.i_c].vec.y, (int)vars->data.b.cam.c[vars->data.b.i_c].vec.z, (int)vars->data.b.cam.c[vars->data.b.i_c].fov);
		mlx_put_image_to_window(vars->mlx, vars->win,
		vars->data.sav[vars->data.b.i_c], 0, 0);
	}
}

static int			cam_change_hooks(int keycode, t_vars *vars)
{
	if (keycode == 124 && vars->data.b.cam.max > 1)
	{
		if (vars->data.sav[vars->data.b.i_c] == NULL)
		{
			vars->data.sav[vars->data.b.i_c] = vars->data.img;
			vars->data.img = mlx_new_image(vars->mlx, vars->data.b.res.x_max, vars->data.b.res.y_max);
			vars->data.addr = mlx_get_data_addr(vars->data.img, &(vars->data.bpp), &(vars->data.len), &(vars->data.endian));
		}
		else
			vars->data.addr = mlx_get_data_addr(vars->data.sav[vars->data.b.i_c], &(vars->data.bpp), &(vars->data.len), &(vars->data.endian));
		if (vars->data.b.i_c == vars->data.b.cam.max - 1)
			vars->data.b.i_c = 0;
		else
			vars->data.b.i_c++;
		saved_images_hooks(vars);
	}
	else if (keycode == 123 && vars->data.b.cam.max > 1)
	{
		if (vars->data.sav[vars->data.b.i_c] == NULL)
		{
			vars->data.sav[vars->data.b.i_c] = vars->data.img;
			vars->data.img = mlx_new_image(vars->mlx, vars->data.b.res.x_max, vars->data.b.res.y_max);
			vars->data.addr = mlx_get_data_addr(vars->data.img, &(vars->data.bpp), &(vars->data.len), &(vars->data.endian));
		}
		else
			vars->data.addr = mlx_get_data_addr(vars->data.sav[vars->data.b.i_c], &(vars->data.bpp), &(vars->data.len), &(vars->data.endian));
		if (vars->data.b.i_c == 0)
			vars->data.b.i_c = vars->data.b.cam.max - 1;
		else
			vars->data.b.i_c--;
		saved_images_hooks(vars);
	}
	return (0);
}

static int			refresh_hooks(t_vars *vars)
{
	// free(vars->data.o);
	ft_printf("Reading...\n");
	// vars->data.o = reader(&vars->data.b, 0, 0);
	while (vars->data.b.cam.c[0].pos.z <= 5.000)
	{
		vars->data.b.cam.c[0].pos.z += 0.001;
	
	// if (vars->data.o == NULL)
	// {
	// 	ft_printf("Can't refresh... check for tabs/other mistakes?\n");
	// 	return (0);
	// }
	// ft_printf("Rendering...\n");
		px_loop(&vars->data);
		for(int i = 1; i < 10000; i++)
		{
		}
	// ft_printf("Done!\n");
		mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
	}
	return (0);
}

static int			button_press_hooks(int keycode, t_vars *vars)
{
	if (keycode == 53 || keycode == 12)
	{
		// reader_free(vars->data.o, vars->data.b.light, vars->data.b.cam.c, NULL);
		exit(mlx_destroy_window(vars->mlx, vars->win) * 0);
	}
	if (keycode == 123 || keycode == 124)
		cam_change_hooks(keycode, vars);
	if (keycode == 15)
		refresh_hooks(vars);
	return (0);
}

static int			destroy_notify_hooks(int x, t_vars *vars)
{
	(void)x;
	(void)vars;
	// reader_free(vars->data.o, vars->data.b.light, vars->data.b.cam.c, NULL);
	ft_printf("\x1b[38;5;196m[-]\x1b[0m Shutting down...\n");
	exit(0);
	return (0);
}

void				hooks(t_vars *vars)
{
	mlx_hook(vars->win, 2, (1L << 0), button_press_hooks, vars);
	mlx_hook(vars->win, 17, 0L, destroy_notify_hooks, vars);
	return ;
}
