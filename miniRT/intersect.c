/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/12 16:47:31 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/07/18 21:57:24 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		inter_sph(t_ray *ray, t_sph sph, t_img_list *dest)
{
	t_vec3 	l;
	float	t;
	float	x;
	float	y;
	float 	t1;
	float	t2;
	float	tnear = INFINITY;

	t1 = INFINITY;
	t2 = INFINITY;
	(void)dest;
	l = vectorSub(&sph.center, &ray->orig);
	t = vectorDot(&l, &ray->norm_dir);
	if (t < 0)
		return (0);
	y = vectorDot(&l, &l) - (t * t);
	if (y > (sph.diam * (sph.diam * 0.25)))
		return (0);
	x = sqrt((sph.diam * (sph.diam * 0.25)) - y);
	t1 = t - x;
	t2 = t + x;
	if (t1 < 0) 
		t1 = t2;
	if (t1 < tnear)
		tnear = t2; 
	// new point = RO + t1, or t2, depending on side of sphere.
	// t1 / t2 are distance from OG, t1 * RD --- t2 * RD are the 2 intersection points.
	return (1);
}

