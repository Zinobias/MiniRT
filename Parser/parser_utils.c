/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/09 18:54:10 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/05 17:48:21 by zgargasc      ########   odam.nl         */
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
		error("Invalid specifier", 18);
	while (i < 9)
	{
		current = &g_f_array[i];
		if (line[0] == current->str[0] && line[1] == current->str[1])
			return (current);
		i++;
	}
	error("Invalid specifier", 18);
	return (0);
}

void			obj_add(t_f_data *obj_data, t_obj_list **head, char *line)
{
	t_obj_list	*current;

	if (!obj_data)
		error("Invalid scene", 14);
	current = *head;
	if (current->obj_type)
	{
		while (current->next != NULL)
			current = current->next;
		current->next = (t_obj_list *)malloc(sizeof(t_obj_list));
		if (!current->next)
			error("Malloc obj struct", 18);
		current = current->next;
		current->next = NULL;
	}
	current->obj_type = obj_data;
	current->object = (*obj_data->function)(line);
}

void			line_handler(char *line, t_obj_list **head)
{
	if (((*line == 'A' && (*head)->rac & 1) ||
		(*line == 'R' && (*head)->rac & 2)))
		error("Multiple R or A", 16);
	if (*line == 'R')
		(*head)->rac |= 2;
	if (*line == 'A')
		(*head)->rac |= 1;
	if (*line == 'c' && line[1] == ' ')
		(*head)->rac |= 4;
	obj_add(line_to_data(line), head, line);
	return ;
}
