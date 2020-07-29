/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/12 16:47:31 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/07/29 06:35:52 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_inter_data	g_f_array_int[5] =
{
	{SPH, &inter_sph},
	{PL, &inter_plane},
	{TR, &inter_triangle},
	{SQ, &inter_square},
	{CY, &inter_cylinder}
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
		while (i < 5)
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
		current = current->next;
	}
}

void	check_hit_l(t_ray **ray, t_obj_list **head, double l)
{
	t_obj_list *current;
	int				i;
	t_hit			hit;
	t_inter_data	*current_f;

	current = *head;
	(*ray)->hit.color = 0;
	(*ray)->hit.t1 = INFINITY;
	(*ray)->hit.check = 0;
	while (current)
	{
		i = 0;
		while (i < 5)
		{
			current_f = &g_f_array_int[i];
			if (current_f->f_code == current->obj_type->f_code)
			{
				hit = (*g_f_array_int[i].function)(*ray, current->object);
				if (hit.check == 1 && (hit.t1 <= l && hit.t1 >= 0))
				{
					(*ray)->hit.check = 1;
					return ;
				}
				break;
			}
			i++;
		}
		current = current->next;
	}
}

t_vec3	sphere_normal(t_ray *ray, t_sph sph, double t)
{
	t_vec3	normal;

	normal = vector_x_d(&ray->norm_dir, t);
	normal = vectorPlus(&normal, &ray->orig);
	normal = vectorSub(&normal, &sph.center);
	return (normal);
}

t_hit	inter_sph(t_ray *ray, t_object sphe)
{
	t_sph	sph;
	t_vec3 	l;
	double txy[3];
	t_hit	hit;

	sph = sphe.sphere;
	l = vectorSub(&sph.center, &ray->orig);
	txy[0] = vectorDot(&l, &ray->norm_dir);
	hit.check = 0;
	hit.t1 = INFINITY;
	hit.t2 = INFINITY;
	hit.color = 0;
	if (txy[0] < 0)
		return (hit);
	txy[2] = vectorDot(&l, &l) - (txy[0] * txy[0]);
	if (txy[2] > (sph.diam * (sph.diam * 0.25)))
		return (hit);
	txy[1] = sqrt((sph.diam * (sph.diam * 0.25)) - txy[2]);
	hit.t1 = txy[0] - txy[1];
	hit.t2 = txy[0] + txy[1];
	hit.color = sph.colors;
	hit.check = 1;
	hit.hit_normal = sphere_normal(ray, sph, hit.t1);
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
			// check normal
			hit.hit_normal = vector_x_d(&pl.norm_vec, -1);
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
	t_inter_tria_vals v;
	
	v.hit.t1 = INFINITY;
	v.hit.check = 0;
	v.tr = triangle.triangle;
	v.n_plane = t_plane_normal(&v.tr);
	v.hit.hit_normal = v.n_plane;
	v.n_dot_rd = vectorDot(&v.n_plane, &ray->norm_dir);
	if (fabs(v.n_dot_rd) < 0.000001)
		return (v.hit);
	v.d = vectorDot(&v.n_plane, &v.tr.point1);
	v.t = -((vectorDot(&v.n_plane, &ray->orig) - v.d) / v.n_dot_rd);
	if (v.t < 0)
		return (v.hit);
	v.p = (t_vec3){ray->orig.x + v.t * ray->norm_dir.x, 
	ray->orig.y + v.t * ray->norm_dir.y, ray->orig.z + v.t * ray->norm_dir.z};
	if (check_tr_in(v.tr.point1, v.tr.point2, &v.p, &v.n_plane) == 1 ||
	 check_tr_in(v.tr.point2, v.tr.point3, &v.p, &v.n_plane) == 1 	|| 
	 check_tr_in(v.tr.point3, v.tr.point1, &v.p, &v.n_plane) == 1)
		return (v.hit);
	v.hit.color = v.tr.colors;
	v.hit.t1 = v.t;
	v.hit.check = 1;
	return (v.hit);
}


t_hit	inter_square(t_ray *ray, t_object sq_)
{
	t_hit		hit[2];
	t_sq		sq;
	t_object	tr[2];
	t_mat4		rot;
	t_vec3		temp[2];

	sq = sq_.square;
	hit[0].check = 0;
	rot = look_at(sq.cords, vectorPlus(&sq.cords, &sq.norm_vec));
	rot = (t_mat4){vector_x_d(&rot.x, sq.side_size * 0.5), 
	vector_x_d(&rot.y, sq.side_size * 0.5),
	rot.z, rot.l};
	temp[0] = vectorPlus(&sq.cords, &rot.y);
	temp[1] = vectorSub(&sq.cords, &rot.y);
	tr[0].triangle = (t_tr){vectorSub(&temp[0], &rot.x), 
	vectorPlus(&temp[1], &rot.x), vectorSub(&temp[1], &rot.x), 
	sq.colors};
	hit[0] = inter_triangle(ray, tr[0]);
	tr[1].triangle = (t_tr){vectorPlus(&temp[0],
	 &rot.x), tr[0].triangle.point1, tr[0].triangle.point2, sq.colors};
	hit[1] = inter_triangle(ray, tr[1]);
	return (hit[1].check == 1 ? hit[1] : hit[0]);
}


//   Ogre::Vector3 AB = B - A;
//   Ogre::Vector3 AO = start - A;
//   Ogre::Vector3 AOxAB = AO.crossProduct(AB);
//   Ogre::Vector3 VxAB  = dir.crossProduct(AB);
//   double ab2 = AB.dotProduct(AB);
//   double a = VxAB.dotProduct(VxAB);
//   double b = 2 * VxAB.dotProduct(AOxAB);
//   double c = AOxAB.dotProduct(AOxAB) - (r*r * ab2);
//   double d = b * b - 4 * a * c;
//   if (d < 0) return;
//   double time = (-b - sqrt(d)) / (2 * a);
//   if (time < 0) return;

// https://github.com/spinatelli/raytracer/blob/master/Cylinder.cpp


t_hit		inter_cylinder(t_ray *ray, t_object obj)
{
	t_vec3	p0;
	double	a;
	double	b;
	double	c;
	double	delta;
	double	epsilon;
	double	t;
	double	y;
	double	dist;
	int		bool[2];
	t_vec3 	cent2;
	t_cy 	cy;
	t_hit	hit;


	cy = obj.cylinder;
	hit = (t_hit){(t_vec3){0,0,0},0,INFINITY,INFINITY, 0, (t_vec3){0,0,0}};
	p0 = vectorSub(&ray->orig, &cy.cords);
	// coefficients for the inter equation
	// mathematically intersecting the line equation with the cylinder equation
	a = ray->norm_dir.x * ray->norm_dir.x + ray->norm_dir.z * ray->norm_dir.z;
	b = ray->norm_dir.x * p0.x + ray->norm_dir.z * p0.z;
	c = p0.x * p0.x + p0.z * p0.z - (cy.dia * (cy.dia * 0.25));
	delta = b * b - a * c;
	// epsilon because of computation errors between doubles
	epsilon = 0.00000001;

	// means no intersections, delta < 0
	if (delta < epsilon)
		return (hit);
	// nearest intersection :
	t = (-b - sqrt(delta)) / a;

	// t <= 0 means target is behind the ray.orig
	if (t <= epsilon)
		return (hit);
	y = p0.y + t * ray->norm_dir.y;

	// check cylinder bases
	if (y > cy.height + epsilon || y < -epsilon)
	{
		bool[0] = intersect_cyl_base(ray, cy.cords, cy.cords, &dist, cy);
		if (bool[0] == 1)
			t = dist;
		cent2 = vector_multiply(&cent2, &(t_vec3){1,1,cy.height});
		bool[1] = intersect_cyl_base(ray, cent2, cy.cords, &dist, cy);
		if (bool[1] == 1 && dist > epsilon && t >= dist)
			t = dist;
		if (bool[0] || bool[1])
		{
			hit.check = 1;
			// hit.color = cy.colors;
			hit.color = rgba(255,0,0,0);
			hit.t1 = t;
		}
			// printf("HIT %lf\n", dist);
		
		return (hit);
	}
	hit.color = cy.colors;
	hit.check = 1;
	hit.t1 = t;
	// printf("HIT %lf\n", t);
	// printf("HIT\n");
	return (hit);
}

int		intersect_cyl_base(t_ray *ray, t_vec3 c, t_vec3 c2, double *t, t_cy cy)
{
	t_vec3	normal;
	t_vec3	p0;
	double	A;
	double	B;
	double	C;
	double	D;
	double	dist;
	double	epsilon;
	double	r;
	r = cy.dia * 0.5;

	dist = 0;
	normal = normalize_cylinder(c, c2, cy);
	epsilon = 0.00000001;
	p0 = (t_vec3){ray->orig.x -c2.x, ray->orig.y - c2.y, ray->orig.z - c2.z};
	A = normal.x;
	B = normal.y;
	C = normal.z;
	D = (A*(c.x-c2.x) + B *(c.y - c2.y)+C * (c.z - c2.z));

	if (A * ray->norm_dir.x + B * ray->norm_dir.y + C * ray->dir.z == 0)
		return (0);

	dist = -(A * p0.x + B * p0.y + C * p0.z + D) /
	(A * ray->norm_dir.x + B * ray->norm_dir.y + C * ray->norm_dir.z);
	if (dist < epsilon)
		return (0);

	t_vec3 p;
	p = (t_vec3){p0.x + dist * ray->norm_dir.x, 
	p0.y + dist * ray->norm_dir.y,
	p0.z + dist * ray->norm_dir.z};
	if (p.x * p.x + p.z * p.z - r * r > epsilon)
		return (0);
	*t = dist;
	return (1);
}
// calculate normal point on a surface
// vertical vector int he base / vecotr
// direction from axis to point
// point is a base;
t_vec3	normalize_cylinder(t_vec3 c, t_vec3 c2, t_cy cy)
{
	t_vec3	new;
	double	epsilon;
	double	r;
	double	h;
	t_vec3	c0;
	r = cy.dia * 0.5;
	h = cy.height;
	epsilon =  0.00000001;
	if (c.x < c2.x + r && c.x > c2.x - r && c.z < c2.z + r && c.z > c2.z - r)
	{
		if (c.y < c2.y + h + epsilon && c.y > c2.y + h - epsilon)
			return ((t_vec3){0,1,0});
		if (c.y < c2.y + epsilon && c.y > c2.y - epsilon)
			return ((t_vec3){0,-1,0});
	}
	c0 = (t_vec3){c2.x, c.y, c2.z};
	new = vectorSub(&c, &c0);
	new = vec_normalize(&new);
	return (new);
}