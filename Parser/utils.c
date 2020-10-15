/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 18:35:54 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/10/15 15:34:36 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_line_valid(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			error("Extra char on line", 19);
		i++;
	}
	return ;
}

void	error(char *message, int char_c)
{
	write(1, "ERROR\n", 7);
	write(1, message, char_c);
	write(1, "\n", 1);
	exit(1);
}

void	l_get_a(t_data **mlx_data, t_obj_list **list)
{
	t_obj_list	*current;

	current = *list;
	if (current->obj_type->f_code == AMB)
	{
		(*mlx_data)->ambient_light = current->object.amb;
		rm_element(list, AMB);
		return ;
	}
	else
		while (current->next)
		{
			if (current->obj_type->f_code == AMB)
				break ;
			current = current->next;
		}
	(*mlx_data)->ambient_light = current->object.amb;
	rm_element(list, AMB);
	return ;
}

void	l_get_r(t_data **mlx_data, t_obj_list **list, int argc)
{
	t_obj_list	*current;
	int			xy[2];

	current = *list;
	if (current->obj_type->f_code != RES)
	{
		while (current->next)
		{
			if (current->obj_type->f_code == RES)
				break ;
			current = current->next;
		}
	}
	if (argc != 3)
	{
		mlx_get_screen_size((*mlx_data)->mlx, &xy[0], &xy[1]);
		current->object.res.x = fmin(xy[0], current->object.res.x);
		current->object.res.y = fmin(xy[1], current->object.res.y);
	}
	(*mlx_data)->res = current->object.res;
	rm_element(list, RES);
	return ;
}

t_vec3	setcam(t_vec3 from, t_img_list *dest)
{
	t_vec3 new;
	t_mat4 c2w;

	if (dest->cam_vals.norm_vec.x == 0 && dest->cam_vals.norm_vec.y == 0
		&& dest->cam_vals.norm_vec.z == 0)
		return (from);
	c2w = look_at(dest->cam_vals.view_p,
		vector_plus(&dest->cam_vals.view_p, &dest->cam_vals.norm_vec));
	new = vec3_x_matrix(&from, &c2w);
	return (new);
}
