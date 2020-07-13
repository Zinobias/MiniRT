/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/12 16:47:31 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/07/13 19:16:29 by zgargasc      ########   odam.nl         */
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

	// sph.center.x = 0;
	// sph.center.y = 5;
	// sph.center.z = 10;
	// sph.diam = 2;
	t1 = INFINITY;
	t2 = INFINITY;
	// printf("x %lf, y %lf, z %lf\n", ray->norm_dir.x, ray->norm_dir.y, ray->norm_dir.z);
	printf("sphere x %lf, y %lf, z %lf\n", sph.center.x, sph.center.y, sph.center.z);
	(void)dest;
	// potentially change ray->norm back to ray->dir
	l = vectorSub(&sph.center, &ray->orig);
	// printf("l = x : %lf, y : %lf z %lf\n", l.x, l.y, l.z);
	// printf("norm_dir = x : %lf, y : %lf z %lf\n", ray->norm_dir.x, ray->norm_dir.y, ray->norm_dir.z);
	t = vectorDot(&l, &ray->dir);
	// printf("t = %lf\n", t);
	if (t < 0)
		return (0);
	y = vectorDot(&l, &l) - (t * t);
	// gotta doublecheck the below check
	// printf("gnananana\n");
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

// int		inter_sph(t_ray *ray, t_sph sph, t_img_list *dest)
// {
// 	(void)dest;
// 	float	r;
// 	float	t;
// 	t_vec3	p;
// 	float	y;
// 	float	x;
// 	float	t1;
// 	float	t2;
// 	t_vec3	temp;
// 	t_vec3 	tempp = vec3(t,t,t);
// 	r = sph.diam / 2;

// 	t = vectorDot(&sph.center - &ray->orig, &ray->norm_dir);
// 	temp = vector_multiply(&ray->norm_dir, &tempp);
// 	p = vectorPlus(&ray->orig, &temp);
// 	y = vectorSub(&sph.center, &p);

// 	if (y < r)
// 		return (1);
// 	return (0);
// }