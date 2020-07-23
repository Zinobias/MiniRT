/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/12 16:47:31 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/07/23 19:51:26 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_inter_data	g_f_array_int[4] =
{
	{SPH, &inter_sph},
	{PL, &inter_plane},
	{TR, &inter_triangle},
	// {CY, &inter_cylinder},
	{TR, &inter_square}
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
		while (i < 4)
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
t_vec3	t_plane_normal(t_tr *tr)
{
	t_vec3	new[2];
	t_vec3	p[3];
	t_vec3	ret;

	p[0] = tr->point1;
	p[1] = tr->point2;
	p[2] = tr->point3;

	new[0].x = p[1].x - p[0].x; 
	new[0].y = p[1].y - p[0].y; 
	new[0].z = p[1].z - p[0].z; 

	new[1].x = p[2].x - p[0].x;
	new[1].y = p[2].y - p[0].y; 
	new[1].z = p[2].z - p[0].z;
	ret = crossproduct(&new[0], &new[1]);
	return (ret);
}

int		check_tr_in(t_vec3 p0, t_vec3 p1, t_vec3 *p_, t_vec3 *n)
{
	t_vec3	edge;
	t_vec3	p[2];
	t_vec3	vp;
	t_vec3	c;

	p[0] = p0;
	p[1] = p1;

	edge.x = p[1].x - p[0].x;
	edge.y = p[1].y - p[0].y;
	edge.z = p[1].z - p[0].z;
	
	vp.x = p_->x - p[0].x;
	vp.y = p_->y - p[0].y; 
 	vp.z = p_->z - p[0].z; 

	c = crossproduct(&edge, &vp);
	if (vectorDot(n, &c) < 0)
		return (1);
	return (0);
}

t_hit	inter_triangle(t_ray *ray, t_object triangle)
{
	t_hit	hit;
	t_tr	tr;
	t_vec3	n_plane;
	t_vec3	p;
	double	n_dot_rd;
	double	d;
	double	t;
	
	hit.t1 = INFINITY;
	hit.check = 0;
	tr = triangle.triangle;
	n_plane = t_plane_normal(&tr);
	n_dot_rd = vectorDot(&n_plane, &ray->norm_dir);
	if (fabs(n_dot_rd) < 0.000001)
		return (hit);
	d = vectorDot(&n_plane, &tr.point1);
	t = -((vectorDot(&n_plane, &ray->orig) - d) / n_dot_rd);
	// t = (vectorDot(&n_plane, &ray->orig) + d) / n_dot_rd;
	if (t < 0)
		return (hit);
	p = vec3(ray->orig.x + t * ray->norm_dir.x, ray->orig.y + t * ray->norm_dir.y, ray->orig.z + t * ray->norm_dir.z);
	if (check_tr_in(tr.point1, tr.point2, &p, &n_plane) == 1 || check_tr_in(tr.point2, tr.point3, &p, &n_plane) == 1 	|| check_tr_in(tr.point3, tr.point1, &p, &n_plane) == 1)
		return (hit);
	hit.color = tr.colors;
	hit.t1 = t;
	hit.check = 1;
	// printf("reeee\n");
	return (hit);
}

t_hit	inter_square(t_ray *ray, t_object sq_)
{
	t_hit		hit;
	t_sq		sq;
	t_object	tr[2];
	t_vec3		p[4];
	double		sq_r;
	t_mat4		rot;
	sq = sq_.square;
	sq_r = sq.side_size / 2;
	hit.check = 0;
	hit.t1 = INFINITY;
	p[0] = vec3(sq.cords.x + sq_r, sq.cords.y + sq_r, sq.cords.z + sq_r);
	p[1] = vec3((sq.cords.x + sq_r), -(sq.cords.y + sq_r), (sq.cords.z + sq_r));
	p[2] = vec3(-(sq.cords.x + sq_r), sq.cords.y + sq_r, sq.cords.z + sq_r);
	p[3] = vec3(sq.cords.x + sq_r, -(sq.cords.y + sq_r), (sq.cords.z + sq_r));
	
	rot = look_at(sq.cords, vectorPlus(&sq.cords, &sq.norm_vec));
	p[0] = vec3_x_matrix(&p[0], &rot);
	p[1] = vec3_x_matrix(&p[1], &rot);
	p[2] = vec3_x_matrix(&p[2], &rot);
	p[3] = vec3_x_matrix(&p[3], &rot);


	tr[0].triangle.point1 = p[0];
	tr[0].triangle.point2 = p[1];
	tr[0].triangle.point3 = p[3];
	tr[0].triangle.colors = sq.colors;
	hit = inter_triangle(ray, tr[0]);
	if (hit.check == 1)
		return(hit);
	tr[1].triangle.point1 = p[0];
	tr[1].triangle.point2 = p[1];
	tr[1].triangle.point3 = p[2];
	tr[1].triangle.colors = sq.colors;
	hit = inter_triangle(ray, tr[1]);
	if (hit.check == 1)
		return (hit);
	return (hit);
}