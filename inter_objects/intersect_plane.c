/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_plane.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 16:28:50 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/10/15 20:51:54 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** https://forums.unrealengine.com/development-discussion/
** rendering/91003-new-to-unreal-planes-become-
** invisible-when-viewing-from-opposite-side
** this is why you see the plane only from one direction. When
** looking straight at it.
** Engines generally use it to reduce computing time.
** back culling, add this statement : if (denom > 1e-6)
** below t vector dot
*/

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
	t = vector_dot(&l, &hit.hit_normal) / denom;
	if (t > 0)
	{
		hit.check = 1;
		hit.t1 = t;
		hit.color = pl.colors;
		hit.obj_type = PL;
		return (hit);
	}
	return (hit);
}
