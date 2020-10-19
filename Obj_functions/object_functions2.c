/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object_functions2.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 21:30:19 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/10/17 17:59:09 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object		get_sphere(char *line)
{
	t_sph		sphere;
	t_f3_ret	f_ret;
	t_d_ret		d_ret;
	int			i;

	i = 2;
	f_ret = get_fields(line + i);
	sphere.center = f_ret.f_info;
	i += f_ret.i;
	d_ret = get_double(line + i);
	sphere.diam = d_ret.val;
	i += d_ret.i;
	while (line[i] == ' ')
		i++;
	f_ret = get_fields(line + i);
	check_vec3_range(f_ret.f_info, 0, 255);
	sphere.colors = rgba(f_ret.f_info.x, f_ret.f_info.y, f_ret.f_info.z);
	i += f_ret.i;
	check_line_valid(line + i);
	if (sphere.diam <= 0)
		error("diameter size is invalid", 25);
	return ((t_object)sphere);
}

t_object		get_square(char *line)
{
	t_sq		square;
	t_f3_ret	f_ret;
	t_d_ret		d_ret;
	int			i;

	i = 2;
	f_ret = get_fields(line + i);
	square.cords = f_ret.f_info;
	i += f_ret.i;
	f_ret = get_fields(line + i);
	check_vec3_range(f_ret.f_info, -1, 1);
	i += f_ret.i;
	square.norm_vec = f_ret.f_info;
	d_ret = get_double(line + i);
	i += d_ret.i;
	square.side_size = d_ret.val;
	f_ret = get_fields(line + i);
	check_vec3_range(f_ret.f_info, 0, 255);
	i += f_ret.i;
	square.colors = rgba(f_ret.f_info.x, f_ret.f_info.y, f_ret.f_info.z);
	check_line_valid(line + i);
	if (square.side_size <= 0)
		error("Invalid sq side size", 21);
	return ((t_object)square);
}

static t_object	check_cyl_range(t_cy cy)
{
	if (cy.dia <= 0 || cy.height <= 0)
		error("Cy dia || height <= 0", 22);
	return ((t_object)cy);
}

t_object		get_cylinder(char *line)
{
	t_cy		cylinder;
	t_f3_ret	f_ret;
	t_d_ret		d_ret;
	int			i;

	i = 2;
	f_ret = get_fields(line + i);
	cylinder.cords = f_ret.f_info;
	i += f_ret.i;
	f_ret = get_fields(line + i);
	check_vec3_range(f_ret.f_info, -1, 1);
	cylinder.norm_vec = f_ret.f_info;
	i += f_ret.i;
	d_ret = get_double(line + i);
	i += d_ret.i;
	cylinder.dia = d_ret.val;
	d_ret = get_double(line + i);
	i += d_ret.i;
	cylinder.height = d_ret.val;
	f_ret = get_fields(line + i);
	check_vec3_range(f_ret.f_info, 0, 255);
	cylinder.colors = rgba(f_ret.f_info.x, f_ret.f_info.y, f_ret.f_info.z);
	i += f_ret.i;
	check_line_valid(line + i);
	return (check_cyl_range(cylinder));
}

t_object		get_triangle(char *line)
{
	t_f3_ret	f_ret;
	t_tr		triangle;
	int			i;

	i = 2;
	f_ret = get_fields(line + i);
	i += f_ret.i;
	triangle.point1 = f_ret.f_info;
	f_ret = get_fields(line + i);
	i += f_ret.i;
	triangle.point2 = f_ret.f_info;
	f_ret = get_fields(line + i);
	i += f_ret.i;
	triangle.point3 = f_ret.f_info;
	f_ret = get_fields(line + i);
	check_vec3_range(f_ret.f_info, 0, 255);
	i += f_ret.i;
	triangle.colors = rgba(f_ret.f_info.x, f_ret.f_info.y, f_ret.f_info.z);
	check_line_valid(line + i);
	return ((t_object)triangle);
}
