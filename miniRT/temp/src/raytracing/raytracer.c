/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raytracer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 12:05:13 by ldideric      #+#    #+#                 */
/*   Updated: 2020/07/04 16:53:03 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

t_vect			hit_checker(t_vect *rd, t_objs *o, t_data *data)
{
	static const t_hit_o hit_o[128] = {
		['s'] = &sphere,
		['p'] = &plane,
		['t'] = &triangle,
	};

	return (hit_o[(int)o->type](rd, data, o));
}

unsigned int	first_hit(t_data *data)
{
	t_rgb	rgb;
	t_vect	hit;
	int		i;

	i = 0;
	rgb.color = 0;
	hit = (t_vect){0, 0, 0, 0};
	while (data->o[i].type)
	{
		if (data->o[i].hit.hit == 1)
		{
			rgb = data->o[i].rgb;
			hit = data->o[i].hit;
			break ;
		}
		i++;
	}
	while (data->o[i].type)
	{
		if (length_betw(hit, data->b.cam.c[data->b.i_c].pos) >
			length_betw(data->o[i].hit, data->b.cam.c[data->b.i_c].pos)
			&& data->o[i].hit.hit == 1)
		{
			rgb = data->o[i].rgb;
			hit = data->o[i].hit;
		}
		i++;
	}
	return (rgb.color);
}

unsigned int	each_px(t_vect *rd, t_data *data)
{
	int i;

	i = 0;
	while (data->o[i].type)
	{
		data->o[i].hit = hit_checker(rd, &data->o[i], data);
		i++;
	}
	return (first_hit(data));
}

void			*px_loop(t_data *data)
{
	t_vect	px_pos;
	t_vect	ray;
	int		x;
	int		y;
	int		i;

	y = 0;
	i = data->b.i_c;
	px_pos.z = -1;
	// ft_printf("\x1b[38;5;83m[+]\x1b[0mCam: %02d/%02d\n", i + 1,	data->b.cam.max);
	// ft_printf("\x1b[38;5;83m[+]\x1b[0mpos:%d,%d,%d - vec:%d,%d,%d - fov:%d\n---\n", (int)data->b.cam.c[i].pos.x, (int)data->b.cam.c[i].pos.y, (int)data->b.cam.c[i].pos.z, (int)data->b.cam.c[i].vec.x, (int)data->b.cam.c[i].vec.y, (int)data->b.cam.c[i].vec.z, (int)data->b.cam.c[i].fov);
	while (y < data->b.res.y_max)
	{
		x = 0;
		px_pos.y = get_ndcy_pos(&data->b, y);
		while (x < data->b.res.x_max)
		{
			px_pos.x = get_ndcx_pos(&data->b, x);
			ray = ft_normalize(vect_min(px_pos, data->b.cam.c[i].pos));
			printf("x : [%lf] -- y : [%lf] -- z : [%lf]\n",ray.x, ray.y, ray.z);
			my_mlx_pixel_put(data, x, y, each_px(&ray, data));
			x++;
		}
		y++;
	}
	return (NULL);
}
