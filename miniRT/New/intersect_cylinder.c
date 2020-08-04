/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_cylinder.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 16:25:57 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/04 02:30:55 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	get_cy_normal(t_ray *ray, t_cy cy)
{
	t_vec3	ret[3];

	ret[0] = vector_x_d(&ray->norm_dir, -1);
	ret[1] = vector_plus(&ray->orig, &ret[0]);
	ret[2] = vector_sub(&ret[1], &cy.cords);
	ret[2] = vec_normalize(&ret[2]);
	return (ret[2]);
}

static void		get_cy_vals(t_cy_vals *v, t_ray *ray, t_cy cy)
{
	t_vec3	temp[3];
	t_vec3	dist;

	dist = vector_sub(&ray->orig, &cy.cords);
	temp[0] = vector_x_d(&cy.norm_vec,
		vector_dot(&ray->norm_dir, &cy.norm_vec));
	v->base[0] = vector_sub(&ray->norm_dir, &temp[0]);
	temp[1] = vector_x_d(&cy.norm_vec, vector_dot(&dist, &cy.norm_vec));
	v->base[1] = vector_sub(&dist, &temp[1]);
	v->abc[0] = vec3_pow(&v->base[0]);
	v->abc[1] = 2.0 * vector_dot(&v->base[0], &v->base[1]);
	v->abc[2] = vec3_pow(&v->base[1]) - pow(cy.dia / 2, 2);
	temp[0] = vector_x_d(&cy.norm_vec, cy.height / 2);
	v->base[0] = vector_sub(&cy.cords, &temp[0]);
	v->base[1] = vector_plus(&cy.cords, &temp[0]);
}

static void		get_dotproducts_cy(t_ray *ray, t_cy_vals *v, t_cy cy, t_hit hit)
{
	t_vec3	temp[3];

	temp[0] = vector_x_d(&ray->norm_dir, hit.t1);
	temp[1] = vector_plus(&ray->orig, &temp[0]);
	temp[2] = vector_sub(&temp[1], &v->base[0]);
	v->dotproduct[0] = vector_dot(&cy.norm_vec, &temp[2]);
	temp[2] = vector_sub(&temp[1], &v->base[1]);
	v->dotproduct[1] = vector_dot(&cy.norm_vec, &temp[2]);
	temp[0] = vector_x_d(&ray->norm_dir, hit.t2);
	temp[1] = vector_plus(&ray->orig, &temp[0]);
	temp[2] = vector_sub(&temp[1], &v->base[0]);
	v->dotproduct[2] = vector_dot(&cy.norm_vec, &temp[2]);
	temp[2] = vector_sub(&temp[1], &v->base[1]);
	v->dotproduct[3] = vector_dot(&cy.norm_vec, &temp[2]);
}

static	void	cy_check_hit(t_cy_vals v, t_hit *hit, t_cy cy, t_ray *ray)
{
	v.ret = INFINITY;
	if (hit->check == 2)
	{
		if (hit->t1 > 1e-6 && v.dotproduct[0] > 0.0 && v.dotproduct[1] < 0.0)
			v.ret = hit->t1;
		if (hit->t2 > 1e-6 && v.dotproduct[2] > 0.0 && v.dotproduct[3] < 0.0)
		{
			if (v.ret != INFINITY)
				v.ret = fmin(hit->t1, hit->t2);
			else
				v.ret = hit->t2;
		}
		if (v.ret > 1e-6)
		{
			hit->t1 = v.ret;
			hit->color = cy.colors;
			hit->check = 1;
			hit->hit_normal = get_cy_normal(ray, cy);
		}
	}
}

t_hit			inter_cylinder(t_ray *ray, t_object obj)
{
	t_cy		cy;
	t_hit		hit;
	t_cy_vals	vals;

	cy = obj.cylinder;
	if (vec3_pow(&cy.norm_vec) != 0)
		cy.norm_vec = vec_normalize(&cy.norm_vec);
	if (cy.norm_vec.x == 0 && cy.norm_vec.y == 0 && cy.norm_vec.z == 0)
		cy.norm_vec = (t_vec3){0, 1, 0};
	hit = (t_hit){(t_vec3){0, 0, 0}, rgba(0, 0, 0, 0),
		INFINITY, INFINITY, 0, (t_vec3){0, 0, 0}, -1};
	get_cy_vals(&vals, ray, cy);
	quad_solve(vals.abc, &hit);
	get_dotproducts_cy(ray, &vals, cy, hit);
	cy_check_hit(vals, &hit, cy, ray);
	return (hit);
}
