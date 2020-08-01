/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_lib3.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 17:50:14 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/01 22:02:43 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3(double x, double y, double z)
{
	t_vec3	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

void	check_vec3_range(t_vec3 data, double min, double max)
{
	if ((data.x > max || data.y > max || data.z > max)
	|| (data.x < min || data.y < min || data.z < min))
		error(INVAL);
}

t_vec3	vec3_x_matrix(t_vec3 *from, t_mat4 *c2w)
{
	t_vec3	new;

	new.x = from->x * c2w->x.x + from->y * c2w->y.x + from->z * c2w->z.x;
	new.y = from->x * c2w->x.y + from->y * c2w->y.y + from->z * c2w->z.y;
	new.z = from->x * c2w->x.z + from->y * c2w->y.z + from->z * c2w->z.z;
	return (new);
}
