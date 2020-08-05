/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   look_at.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 17:52:42 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/05 17:48:07 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat4	look_at(t_vec3 from, t_vec3 to)
{
	t_mat4	new;
	t_vec3	temp;
	t_vec3	norm;

	norm = vector_sub(&to, &from);
	norm = vec_normalize(&norm);
	if (norm.x == 0.0 && norm.z == 0.0 && fabs(norm.y) == 1.0)
	{
		new.x = norm.y == 1.0 ? vec3(1.0, 0.0, 0.0) : vec3(0.0, 0.0, 1.0);
		new.y = norm.y == 1.0 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
		new.z = norm.y == 1.0 ? vec3(0.0, 1.0, 0.0) : vec3(0.0, -1.0, 0.0);
		return (new);
	}
	temp = vec3(0.0, 1.0, 0.0);
	temp = vec_normalize(&temp);
	new.z = vector_sub(&from, &to);
	new.z = vec_normalize(&new.z);
	new.x = crossproduct(&temp, &new.z);
	new.y = crossproduct(&new.z, &new.x);
	new.l = vec3(0, 0, 0);
	return (new);
}
/*
** new.z = forward vector
** new.x = right
** new.y = uppguide
** new.l = translation vector
** if norm.x / z && y are at these specific cords, it is a
** achilles heel of the look-up function, thus it has to be hardcoded
** Because When the camera is vertical looking straight down or straight up,
** the forward axis gets very close to the
** arbitrary axis used to compute the right axis.
** thus the crossproduct won't have a valid result.
*/
