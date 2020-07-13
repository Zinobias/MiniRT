/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_lib.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/13 17:41:11 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/07/13 17:41:37 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec_normalize(t_vec3 *vec3_, float N)
{
	t_vec3	temp;

	temp.x = vec3_->x / N;
	temp.y = vec3_->y / N;
	temp.z = vec3_->z / N;
	return(temp);
}

t_vec3 vectorSub(t_vec3 *v1, t_vec3 *v2)
{
	return (vec3(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z));
}

double vectorDot(t_vec3 *v1, t_vec3 *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vec3 vectorPlus(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	res;

	res.x = v1->x + v2->x; 
	res.y = v1->y + v2->y;
	res.z =	v1->z + v2->z;
	return (res);
}

t_vec3	vector_multiply(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	new;

	new.x = v1->x * v2->x;
	new.y = v1->y * v2->y;
	new.z = v1->z * v2->z;
	return (new);
}