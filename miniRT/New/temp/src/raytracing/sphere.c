/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/25 19:19:10 by ldideric      #+#    #+#                 */
/*   Updated: 2020/06/11 16:19:23 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

t_vect			sphere(t_vect *rd, t_data *data, t_objs *o)
{
	t_vect p;
	double t;
	double x;
	double y;

	t = dot(vect_min(o->pos1, data->b.cam.c[data->b.i_c].pos), *rd);
	p = (t_vect){rd->x * t, rd->y * t, rd->z * t, 0};
	p = vect_plus(data->b.cam.c[data->b.i_c].pos, p);
	y = length(vect_min(o->pos1, p));
	if (y < o->dia / 2)
	{
		x = sqrt(o->dia / 2 * o->dia / 2 - y * y);
		t = (t - x > t + x) ? t + x : t - x;
		p = (t_vect){rd->x * t, rd->y * t, rd->z * t, 0};
		p = vect_plus(p, data->b.cam.c[data->b.i_c].pos);
		p.hit = 1;
		return (p);
	}
	return ((t_vect){0, 0, 0, 0});
}
