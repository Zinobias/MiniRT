/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   obj_functions1.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 19:29:08 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/10/19 14:57:34 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	get_res(char *line)
{
	t_res	ret;
	t_d_ret	double_ret;
	int		i;

	i = 1;
	double_ret = get_double(line + i);
	ret.x = double_ret.val;
	i += double_ret.i;
	double_ret = get_double(line + i);
	ret.y = double_ret.val;
	i += double_ret.i;
	while (line[i])
	{
		if (line[i] != ' ')
			error("Invalid scene", 14);
		i++;
	}
	if (ret.x < 1 || ret.y < 1)
		error("RES INVALID", 12);
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
		error("Invalid amb", 12);
	amb.colors = rgba(f_ret.f_info.x, f_ret.f_info.y, f_ret.f_info.z);
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
		error("invalid cam fov", 16);
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
		error("invalid light brightness", 25);
	light.brightness = d_ret.val;
	i += d_ret.i;
	f_ret = get_fields(line + i);
	check_vec3_range(f_ret.f_info, 0, 255);
	light.colors = rgba(f_ret.f_info.x, f_ret.f_info.y, f_ret.f_info.z);
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
	plane.colors = rgba(f_ret.f_info.x, f_ret.f_info.y, f_ret.f_info.z);
	i += f_ret.i;
	check_line_valid(line + i);
	return ((t_object)plane);
}
