/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 18:54:10 by zgargasc       #+#    #+#                */
/*   Updated: 2020/03/12 18:56:55 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_f_data	g_f_array[9] =
{
	{RES, "R ", &get_res},
	{AMB, "A ", &get_amb},
	{CAM, "c ", &get_cam},
	{LIGHT, "l ", &get_light},
	{SPH, "sp", &get_sphere},
	{PL, "pl", &get_plane},
	{SQ, "sq", &get_square},
	{CY, "cy", &get_cylinder},
	{TR, "tr", &get_triangle}
};

t_f_data		*line_to_data(char *line)
{
	int			i;
	t_f_data	*current;

	i = 0;
	current = NULL;
	if (line[2] != ' ' && line[1] != ' ')
		error(INVAL);
	while (i < 9)
	{
		current = &g_f_array[i];
		if (line[0] == current->str[0] && line[1] == current->str[1])
			return (current);
		i++;
	}
	error(INVAL);
	return (0);
}

void			obj_add(t_f_data *obj_data, t_obj_list **head, char *line)
{
	t_obj_list	*current;

	if (!obj_data)
		error(INVAL);
	current = *head;
	if (current->obj_type)
	{
		while (current->next)
			current = current->next;
		current->next = (t_obj_list *)malloc(sizeof(t_obj_list));
		if (!current->next)
			error(MALLOC);
		current = current->next;
	}
	current->obj_type = obj_data;
	current->object = (*obj_data->function)(line);
}

void			line_handler(char *line, t_obj_list **head)
{
	static	int	ra;

	if (((*line == 'A' && ra & 1) || (*line == 'R' && ra & 2)))
		error(INVAL);
	if (*line == 'R')
		ra |= 1;
	if (*line == 'A')
		ra |= 2;
	obj_add(line_to_data(line), head, line);
	return ;
}

t_f3_ret		get_fields(char *line)
{
	t_f3_ret	data;
	t_atod_ret	atod_ret;

	data.fields = 0;
	data.i = 0;
	while (line[data.i] == ' ' && line[data.i])
		data.i++;
	if (line[data.i] >= '0' || line[data.i] <= '9' || line[data.i] == '-')
	{
		atod_ret = ft_atod(line + data.i);
		data.i += atod_ret.i;
		if (data.fields == 0)
			data.f_info.x = atod_ret.val;
		if (data.fields == 1)
			data.f_info.y = atod_ret.val;
		if (data.fields == 2)
			data.f_info.z = atod_ret.val;
		data.fields++;
		data.i++;
	}
	if (data.fields != 2 || line[data.i] != ' ')
		error(INVAL);
	return (data);
}

t_d_ret			get_double(char *line)
{
	t_d_ret		ret;
	t_atod_ret	atod_data;

	ret.val = 0;
	ret.i = 0;
	while (line[ret.i] == ' ')
		ret.i++;
	if (line[ret.i] >= '0' || line[ret.i] <= '9' || line[ret.i] == '-')
	{
		atod_data = ft_atod(line + ret.i);
		ret.val = atod_data.val;
		ret.i += atod_data.i;
		ret.i++;
	}
	else if ((line[ret.i] >= '0' || line[ret.i] <= '9')
	|| line[ret.i] != ' ')
		error(INVAL);
	return (ret);
}

t_i_ret			get_int(char *line)
{
	t_i_ret		ret;
	t_atod_ret	atod_data;
	int			i;

	ret.val = 0;
	ret.i = 0;
	while (line[ret.i] == ' ')
		ret.i++;
	i = line[ret.i] == '-' ? ret.i + 1 : ret.i;
	while (line[i] >= '0' || line[i] <= '9')
		i++;
	if (line[i + 1] != ' ')
		error(INVAL);
	if (line[ret.i] >= '0' || line[ret.i] <= '9' || line[ret.i] == '-')
	{
		atod_data = ft_atod(line + ret.i);
		ret.val = atod_data.val;
		ret.i += atod_data.i;
		ret.i++;
	}
	return (ret);
}
