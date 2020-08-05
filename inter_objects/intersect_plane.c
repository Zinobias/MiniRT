/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_plane.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 16:28:50 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/05 17:54:00 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	inter_plane(t_ray *ray, t_object plane)
{
	t_pl	pl;
	t_hit	hit;
	double	denom;
	double	t;
	t_vec3	l;

	hit.t1 = INFINITY;
	hit.check = 0;
	pl = plane.plane;
	l = vector_sub(&pl.cords, &ray->orig);
	hit.hit_normal = vector_x_d(&pl.norm_vec, -1);
	denom = vector_dot(&hit.hit_normal, &ray->norm_dir);
	if (denom > 1e-6)
	{
		t = vector_dot(&l, &hit.hit_normal) / denom;
		if (t > 0)
		{
			hit.check = 1;
			hit.t1 = t;
			hit.color = pl.colors;
			hit.obj_type = PL;
			return (hit);
		}
	}
	return (hit);
}
