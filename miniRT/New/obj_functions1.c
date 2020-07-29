/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_functions1.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 19:29:08 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/07/29 05:02:59 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	get_res(char *line)
{
	t_res	ret;
	t_i_ret	int_ret;
	int		i;
	
	i = 1;
	int_ret = get_int(line + i);
	ret.x = (int)int_ret.val;
	i += int_ret.i;
	int_ret = get_int(line + i);
	ret.y = int_ret.val;
	i += int_ret.i;
	while (line[i])
	{
		if (line[i] != ' ')
			error(INVAL);
		i++;
	}
	return ((t_object)ret);
}

t_object	get_amb(char *line)
{
	t_d_ret		d_ret;
	t_amb		amb;
	t_f3_ret	f_ret;
	int			i;

	i = 1;
	d_ret = get_double(line + i);
	i += d_ret.i;
	amb.ratio = d_ret.val;
	f_ret = get_fields(line + i);
	i += f_ret.i;
	if ((f_ret.f_info.x > 255 || f_ret.f_info.y > 255 || f_ret.f_info.z > 255)
	|| (f_ret.f_info.x < 0 || f_ret.f_info.y < 0 || f_ret.f_info.z < 0)
	|| amb.ratio < 0 || amb.ratio > 1)
		error(INVAL);
	amb.colors = rgba(f_ret.f_info.x, f_ret.f_info.y, f_ret.f_info.z, 0);
	check_line_valid(line + i);
	return ((t_object)amb);
}

t_object	get_cam(char *line)
{
	t_cam		cam;
	t_f3_ret	f_ret;
	t_i_ret		i_ret;
	int			i;

	i = 1;
	f_ret = get_fields(line + i);
	cam.view_p = f_ret.f_info;
	i += f_ret.i;
	f_ret = get_fields(line + i);
	check_vec3_range(f_ret.f_info, -1, 1);
	cam.norm_vec = f_ret.f_info;
	i += f_ret.i;
	i_ret = get_int(line + i);
	if (i_ret.val > 180 || i_ret.val < 0)
		error(INVAL);
	i += i_ret.i;
	cam.fov = i_ret.val;
	check_line_valid(line + i);
	return ((t_object)cam);
}

t_object	get_light(char *line)
{
	t_light		light;
	t_f3_ret	f_ret;
	t_d_ret		d_ret;
	int			i;

	i = 1;
	f_ret = get_fields(line + i);
	light.light_p = f_ret.f_info;
	i += f_ret.i;
	d_ret = get_double(line + i);
	if (d_ret.val < 0.0 || d_ret.val > 1.0)
		error(INVAL);
	light.brightness = d_ret.val;
	i += d_ret.i;
	f_ret = get_fields(line + i);
	check_vec3_range(f_ret.f_info, 0, 255);
	light.colors = rgba(f_ret.f_info.x, f_ret.f_info.y, f_ret.f_info.z, 0);
	i += f_ret.i;
	check_line_valid(line + i);
	return ((t_object)light);
}

t_object	get_plane(char *line)
{
	t_f3_ret	f_ret;
	t_pl		plane;
	int			i;

	i = 2;
	f_ret = get_fields(line + i);
	plane.cords = f_ret.f_info;
	i += f_ret.i;
	f_ret = get_fields(line + i);
	check_vec3_range(f_ret.f_info, -1, 1);
	i += f_ret.i;
	plane.norm_vec = f_ret.f_info;
	f_ret = get_fields(line + i);
	check_vec3_range(f_ret.f_info, 0, 255);
	plane.colors = rgba(f_ret.f_info.x, f_ret.f_info.y, f_ret.f_info.z, 0);
	i += f_ret.i;
	check_line_valid(line + i);
	return ((t_object)plane);
}

t_object	get_sphere(char *line)
{
	t_sph		sphere;
	t_f3_ret	f_ret;
	t_i_ret		i_ret;
	int			i;

	i = 2;
	f_ret = get_fields(line + i);
	sphere.center = f_ret.f_info;
	i += f_ret.i;
	i_ret = get_int(line + i);
	sphere.diam = i_ret.val;
	i += i_ret.i;
	while (line[i] == ' ')
		i++;
	f_ret = get_fields(line + i);
	check_vec3_range(f_ret.f_info, 0, 255);
	sphere.colors = rgba(f_ret.f_info.x, f_ret.f_info.y, f_ret.f_info.z, 0);
	i += f_ret.i;
	check_line_valid(line + i);
	return ((t_object)sphere);
}

t_object	get_square(char *line)
{
	t_sq		square;
	t_f3_ret	f_ret;
	t_i_ret		i_ret;
	int			i;

	i = 2;
	f_ret = get_fields(line + i);
	square.cords = f_ret.f_info;
	i += f_ret.i;
	f_ret = get_fields(line + i);
	check_vec3_range(f_ret.f_info, -1, 1);
	i += f_ret.i;
	square.norm_vec = f_ret.f_info;
	i_ret = get_int(line + i);
	i += i_ret.i;
	square.side_size = i_ret.val;
	f_ret = get_fields(line + i);
	check_vec3_range(f_ret.f_info, 0, 255);
	i += f_ret.i;
	square.colors = rgba(f_ret.f_info.x, f_ret.f_info.y, f_ret.f_info.z, 0);
	check_line_valid(line + i);
	return ((t_object)square);
}

t_object	get_cylinder(char *line)
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
	cylinder.colors = rgba(f_ret.f_info.x, f_ret.f_info.y, f_ret.f_info.z, 0);
	i += f_ret.i;
	check_line_valid(line + i);
	return ((t_object)cylinder);
}

t_object	get_triangle(char *line)
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
	triangle.colors = rgba(f_ret.f_info.x, f_ret.f_info.y, f_ret.f_info.z, 0);
	check_line_valid(line + i);
	return ((t_object)triangle);
}
