/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_sphere.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 16:29:24 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/10/10 21:34:57 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	sphere_normal(t_ray *ray, t_sph sph, double t)
{
	t_vec3	normal;

	normal = vector_x_d(&ray->norm_dir, t);
	normal = vector_plus(&normal, &ray->orig);
	normal = vector_sub(&normal, &sph.center);
	return (normal);
}

static void		check_sph_inter(t_hit *hit)
{
	double	temp;

	if (hit->t1 > hit->t2)
	{
		temp = hit->t1;
		hit->t1 = hit->t2;
		hit->t2 = temp;
	}
	if (hit->t1 < 0)
	{
		hit->t1 = hit->t2;
		if (hit->t1 < hit->t2)
			hit->check = 0;
	}
}

t_hit			inter_sph(t_ray *ray, t_object sphe)
{
	t_sph	sph;
	t_vec3	l;
	double	txy[3];
	t_hit	hit;

	sph = sphe.sphere;
	l = vector_sub(&sph.center, &ray->orig);
	txy[0] = vector_dot(&l, &ray->norm_dir);
	hit.check = 0;
	hit.t1 = INFINITY;
	hit.t2 = INFINITY;
	hit.color = 0;
	if (txy[0] < 0)
		return (hit);
	txy[2] = vector_dot(&l, &l) - txy[0] * txy[0];
	if (txy[2] > (sph.diam * (sph.diam * 0.25)))
		return (hit);
	txy[1] = sqrt((sph.diam * (sph.diam * 0.25)) - txy[2]);
	hit.t1 = txy[0] - txy[1];
	hit.t2 = txy[0] + txy[1];
	hit.color = sph.colors;
	hit.check = 1;
	check_sph_inter(&hit);
	hit.hit_normal = sphere_normal(ray, sph, hit.t1);
	return (hit);
}
