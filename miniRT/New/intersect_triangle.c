/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_triangle.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 16:30:12 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/03 17:55:35 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	t_plane_normal(t_tr *tr)
{
	t_vec3			new[2];
	t_vec3			p[3];
	t_vec3			ret;

	p[0] = tr->point1;
	p[1] = tr->point2;
	p[2] = tr->point3;
	new[0].x = p[1].x - p[0].x;
	new[0].y = p[1].y - p[0].y;
	new[0].z = p[1].z - p[0].z;
	new[1].x = p[2].x - p[0].x;
	new[1].y = p[2].y - p[0].y;
	new[1].z = p[2].z - p[0].z;
	ret = crossproduct(&new[0], &new[1]);
	ret = vec_normalize(&ret);
	return (ret);
}

static int		check_tr_in(t_vec3 p0, t_vec3 p1, t_vec3 *p_, t_vec3 *n)
{
	t_vec3			edge;
	t_vec3			p[2];
	t_vec3			vp;
	t_vec3			c;

	p[0] = p0;
	p[1] = p1;
	edge.x = p[1].x - p[0].x;
	edge.y = p[1].y - p[0].y;
	edge.z = p[1].z - p[0].z;
	vp.x = p_->x - p[0].x;
	vp.y = p_->y - p[0].y;
	vp.z = p_->z - p[0].z;
	c = crossproduct(&edge, &vp);
	if (vector_dot(n, &c) < 0)
		return (1);
	return (0);
}

t_hit			inter_triangle(t_ray *ray, t_object triangle)
{
	t_inter_tria_vals v;

	v.hit.t1 = INFINITY;
	v.hit.check = 0;
	v.tr = triangle.triangle;
	v.n_plane = t_plane_normal(&v.tr);
	v.hit.hit_normal = v.n_plane;
	v.n_dot_rd = vector_dot(&v.n_plane, &ray->norm_dir);
	if (fabs(v.n_dot_rd) < 0.000001)
		return (v.hit);
	v.d = vector_dot(&v.n_plane, &v.tr.point1);
	v.t = -((vector_dot(&v.n_plane, &ray->orig) - v.d) / v.n_dot_rd);
	if (v.t < 0)
		return (v.hit);
	v.p = (t_vec3){ray->orig.x + v.t * ray->norm_dir.x,
	ray->orig.y + v.t * ray->norm_dir.y, ray->orig.z + v.t * ray->norm_dir.z};
	if (check_tr_in(v.tr.point1, v.tr.point2, &v.p, &v.n_plane) == 1 ||
		check_tr_in(v.tr.point2, v.tr.point3, &v.p, &v.n_plane) == 1 ||
		check_tr_in(v.tr.point3, v.tr.point1, &v.p, &v.n_plane) == 1)
		return (v.hit);
	v.hit.color = v.tr.colors;
	v.hit.t1 = v.t;
	v.hit.check = 1;
	return (v.hit);
}
