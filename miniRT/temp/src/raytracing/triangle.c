/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   triangle.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/25 19:02:31 by ldideric      #+#    #+#                 */
/*   Updated: 2020/06/25 16:27:12 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

static int		tr_right_side(t_vect v0, t_vect v1, t_vect p, t_vect n)
{
	t_vect edge;
	t_vect vp;
	t_vect c;

	edge = vect_min(v1, v0);
	vp = vect_min(p, v0);
	c = cross_pr(edge, vp);
	return (dot(n, c) >= 0);
}

static int		tr_normal_check(t_vect *rd, t_data *data, t_objs *o)
{
	t_vect		n;
	double		t;
	double		d;

	n = cross_pr(vect_min(o->pos2, o->pos1), vect_min(o->pos3, o->pos1));
	if (fabs(dot(n, *rd)) < 0.00001)
		return (-1);
	d = dot(n, o->pos1);
	t = (dot(n, data->b.cam.c[data->b.i_c].pos) + d) / dot(n, *rd);
	if (t < 0)
		return (0);
	return (1);
}

t_vect			triangle(t_vect *rd, t_data *data, t_objs *o)
{
	t_vect	n;
	t_vect	p;
	double	t;
	double	d;

	if (o->normal == -1)
		o->normal = tr_normal_check(rd, data, o);
	n = cross_pr(vect_min(o->pos2, o->pos1), vect_min(o->pos3, o->pos1));
	n = (o->normal == 0) ? vec3(n.x * -1, n.y * -1, n.z * -1) : n;
	if (fabs(dot(n, *rd)) < 0.00001)
		return ((t_vect){0, 0, 0, 0});
	d = dot(n, o->pos1);
	t = (dot(n, data->b.cam.c[data->b.i_c].pos) + d) / dot(n, *rd);
	// printf("%f|%f\n", dot(n, *rd), t);
	if (t < 0)
		return ((t_vect){0, 0, 0, 0});
	p = vec3(rd->x * t, rd->y * t, rd->z * t);
	p = vect_plus(data->b.cam.c[data->b.i_c].pos, p);
	if (tr_right_side(o->pos1, o->pos2, p, n) == 0 ||
		tr_right_side(o->pos2, o->pos3, p, n) == 0 ||
		tr_right_side(o->pos3, o->pos1, p, n) == 0)
		return ((t_vect){0, 0, 0, 0});
	p.hit = 1;
	// printf("[HIT]%f,%f,%f,%d\n", p.x, p.y, p.z, p.hit);
	return (p);
}
