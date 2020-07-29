/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 19:39:41 by ldideric      #+#    #+#                 */
/*   Updated: 2020/06/25 16:13:49 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

t_vect			plane(t_vect *rd, t_data *data, t_objs *o)
{
	t_vect	p0l0;
	t_vect	p;
	double	denom;
	double	t;

	denom = dot(o->vec, *rd);
	// printf("%f\n ", denom);
	if (denom <= 1e-6)
		return ((t_vect){0, 0, 0, 0});
	p0l0 = vect_min(o->pos1, data->b.cam.c[data->b.i_c].pos);
	t = dot(p0l0, o->vec) / denom;
	// printf("%f\n", t);
	if (t < 0)
		return ((t_vect){0, 0, 0, 0});
	p = vec3(rd->x * t, rd->y * t, rd->z * t);
	p = vect_plus(data->b.cam.c[data->b.i_c].pos, p);
	p.hit = 1;
	return (p);
}
