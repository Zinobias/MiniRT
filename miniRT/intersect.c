/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/12 16:47:31 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/07/12 18:00:49 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		inter_sph(t_ray *ray, t_sph sph, t_img_list *dest)
{
	t_vec3 	l;
	float	t;
	float	thc;
	float	d2;
	float 	t1;
	float	t2;
	float	tnear = INFINITY;

	t1 = INFINITY;
	t2 = INFINITY;

	l = vectorSub(&sph.center, &ray->orig);
	t = vectorDot(&l, &ray->dir);
	if (t < 0)
		return (0);
	d2 = vectorDot(&l, &l) - (t * t);
	if (d2 > (sph.diam * (sph.diam * 0.25)));
		return (0);
	thc = sqrt((sph.diam * 0.5) - d2);
	t1 = t - thc;
	t2 = t + thc;
	if (t1 < 0) 
		t1 = t2;
	if (t1 < tnear)
		tnear = t2; 
	return (1);
}

