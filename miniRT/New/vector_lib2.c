/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_lib2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 17:49:27 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/05 17:48:34 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vector_x_d(t_vec3 *v1, double d)
{
	t_vec3	new;

	new.x = v1->x * d;
	new.y = v1->y * d;
	new.z = v1->z * d;
	return (new);
}

t_vec3	crossproduct(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	new;

	new.x = v1->y * v2->z - v1->z * v2->y;
	new.y = v1->z * v2->x - v1->x * v2->z;
	new.z = v1->x * v2->y - v1->y * v2->x;
	return (new);
}

t_mat4	mat4(t_vec3 x, t_vec3 y, t_vec3 z, t_vec3 l)
{
	t_mat4 new;

	new.x = x;
	new.y = y;
	new.z = z;
	new.l = l;
	return (new);
}

double	vec3_pow(t_vec3 *v)
{
	return (pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
}

double	v_dot_s(t_vec3 *x, t_vec3 *y, t_vec3 *z)
{
	double	res;
	t_vec3	temp;

	temp = vector_sub(y, z);
	res = vector_dot(x, &temp);
	return (res);
}
