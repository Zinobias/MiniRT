/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect_square.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 16:31:05 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/03 17:59:08 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	inter_square(t_ray *ray, t_object sq_)
{
	t_hit		hit[2];
	t_sq		sq;
	t_object	tr[2];
	t_mat4		rot;
	t_vec3		temp[2];

	sq = sq_.square;
	hit[0].check = 0;
	rot = look_at(sq.cords, vector_plus(&sq.cords, &sq.norm_vec));
	rot = (t_mat4){vector_x_d(&rot.x, sq.side_size * 0.5),
	vector_x_d(&rot.y, sq.side_size * 0.5),
	rot.z, rot.l};
	temp[0] = vector_plus(&sq.cords, &rot.y);
	temp[1] = vector_sub(&sq.cords, &rot.y);
	tr[0].triangle = (t_tr){vector_sub(&temp[0], &rot.x),
	vector_plus(&temp[1], &rot.x), vector_sub(&temp[1], &rot.x),
		sq.colors};
	hit[0] = inter_triangle(ray, tr[0]);
	tr[1].triangle = (t_tr){vector_plus(&temp[0],
		&rot.x), tr[0].triangle.point1, tr[0].triangle.point2, sq.colors};
	hit[1] = inter_triangle(ray, tr[1]);
	hit[1].hit_normal = hit[0].hit_normal;
	return (hit[1].check == 1 ? hit[1] : hit[0]);
}
