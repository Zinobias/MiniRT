/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/12 16:47:31 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/07/22 22:33:32 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_inter_data	g_f_array_int[2] =
{
	{SPH, &inter_sph},
	{PL, &inter_plane}
	// {SQ, &inter_square},
	// {CY, &inter_cylinder},
	// {TR, &inter_triangle}
};

// plane, sphere, cylinder, square
// and triangle.
void	check_hit(t_ray **ray, t_obj_list **head)
{
	t_obj_list *current;
	int				i;
	t_hit			hit;
	t_inter_data	*current_f;

	current = *head;
	(*ray)->hit.color = 0;
	(*ray)->hit.t1 = INFINITY;
	while (current)
	{
		i = 0;
		while (i < 2)
		{
			current_f = &g_f_array_int[i];
			if (current_f->f_code == current->obj_type->f_code)
			{
				hit = (*g_f_array_int[i].function)(*ray, current->object);
				if (hit.t1 < (*ray)->hit.t1 && hit.check == 1)
					(*ray)->hit = hit;
				break;
			}
			i++;
		}
		// hit = (*g_f_array_int[i].function)(*ray, current->object);
		// if (hit.t1 > (*ray)->hit.t1 && hit.check == 1)
		// 	(*ray)->hit = hit;
		// if return of temp < old distance, replace.
		current = current->next;
	}
}

t_hit	inter_sph(t_ray *ray, t_object sphe)
{
	t_sph	sph;
	t_vec3 	l;
	float	t;
	float	x;
	float	y;
	t_hit	hit;

	sph = sphe.sphere;
	l = vectorSub(&sph.center, &ray->orig);
	t = vectorDot(&l, &ray->norm_dir);
	hit.check = 0;
	hit.t1 = INFINITY;
	hit.t2 = INFINITY;
	hit.color = 0;
	if (t < 0)
		return (hit);
	y = vectorDot(&l, &l) - (t * t);
	if (y > (sph.diam * (sph.diam * 0.25)))
		return (hit);
	x = sqrt((sph.diam * (sph.diam * 0.25)) - y);
	hit.t1 = t - x;
	hit.t2 = t + x;
	hit.color = sph.colors;
	hit.check = 1;
	return (hit);
}

t_hit	inter_plane(t_ray *ray, t_object plane)
{
	t_pl	pl;
	t_hit	hit;
	double	denom;
	double	t;
	t_vec3	l;

	hit.t1 = INFINITY;
	hit.check = 0;
	pl = plane.plane;
	l = vectorSub(&pl.cords, &ray->orig);
	denom = vectorDot(&pl.norm_vec, &ray->norm_dir);
    if (denom > 1e-6) 
	{ 
        t = vectorDot(&l, &pl.norm_vec) / denom;
		if (t >= 0)
		{
			hit.check = 1;
			hit.t1 = t;
			hit.color = pl.colors;
			return (hit);
		}
	}
	return (hit);

}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
t_hit	inter_triangle(t_ray *ray, t_object triangle)
{
	t_hit	hit;
	t_tr	tr;
	t_vec3	edges[3];
	double	d;

	tr = triangle.triangle;
	d = vectorDot(,&tr.point1);

	return (hit);
}
// t_hit				inter_square(t_ray *ray, t_object square)
// {
// 	t_sq	sq;
// 	t_hit	hit;
// 	t_vec3	l;
// 	t_vec3	l2;
// 	t_vec3	p[4];

// 	double	t;
// 	double	denom;
// 	sq = square.square;
// 	double	sq_r;
// 	sq_r	= sq.side_size / 2;

// 	p[0] = vec3(sq.cords.x + sq_r, sq.cords.y + sq_r, sq.cords.z + sq_r);
// 	p[1] = vec3(-(sq.cords.x + sq_r), -(sq.cords.y + sq_r), -(sq.cords.z + sq_r));
// 	p[2] = vec3(-(sq.cords.x + sq_r), sq.cords.y + sq_r, sq.cords.z + sq_r);
// 	p[3] = vec3(sq.cords.x + sq_r, -(sq.cords.y + sq_r), -(sq.cords.z + sq_r));

// 	l = vectorSub(&p[0], &p[1]);
// 	l2 = vectorSub(&p[1], &p[3]);
// 	crossproduct();
// 	denom = vectorDot(&sq.norm_vec, &ray->norm_dir);
// 	if (denom > (sq.side_size / 2));
	
// 	// https://www.youtube.com/watch?v=Ff0jJyyiVyw
	
// 	return (hit);
// }
