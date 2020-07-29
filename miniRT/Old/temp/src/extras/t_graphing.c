/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_graphing.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/04 20:15:54 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/09 15:54:13 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

static int			graph_fix(int i, int max, char c)
{
	int new;

	new = i - (max / 2);
	if (c == 'y')
		new = -new;
	if (new > (max / 2))
		new = new - (max / 2);
	return (new);
}

static int			graph_red(int x, int y)
{
	if (x == 0 || y == 0 || x == 1 || y == 1 || x == -1 || y == -1)
		return (1);
	if (y == x || y == -x || y == 2 * x || y == 0.5 * x ||
		y == -2 * x || y == -0.5 * x)
		return (1);
	if (y == x + 1 || y == -x + 1 || y == 2 * x + 1 ||
		y == 0.5 * x + 1 || y == -2 * x + 1 || y == -0.5 * x + 1)
		return (1);
	if (y == x - 1 || y == -x - 1 || y == 2 * x - 1 ||
		y == 0.5 * x - 1 || y == -2 * x - 1 || y == -0.5 * x - 1)
		return (1);
	return (0);
}

static void			graph_back(t_vect pos, t_vect grp, t_data *img)
{
	if (grp.x == 0 || grp.y == 0)
		my_mlx_pixel_put(img, pos.x, pos.y, 0x00000000);
	else if ((int)grp.x % 20 == 0 || (int)grp.y % 20 == 0)
		my_mlx_pixel_put(img, pos.x, pos.y, 0x00BBBBBB);
	else
		my_mlx_pixel_put(img, pos.x, pos.y, 0x00FFFFFF);
}

void				graphing(t_data *img, int x_max, int y_max)
{
	t_vect pos;
	t_vect grp;

	pos.x = 0;
	pos.y = 0;
	while (pos.x < x_max)
	{
		while (pos.y < y_max)
		{
			grp.x = graph_fix(pos.x, x_max, 'x');
			grp.y = graph_fix(pos.y, y_max, 'y');
			if (graph_red(grp.x, grp.y) == 1)
				my_mlx_pixel_put(img, pos.x, pos.y, 0x00FF0000);
			else if ((grp.x * grp.x) + (grp.y * grp.y) <= 2000)
				my_mlx_pixel_put(img, pos.x, pos.y, 0x00000000);
			else if ((grp.x * grp.x) + (grp.y * grp.y) <= 15000)
				my_mlx_pixel_put(img, pos.x, pos.y, 0x000000FF);
			else
				graph_back(pos, grp, img);
			pos.y++;
		}
		pos.x++;
		pos.y = 0;
	}
}
