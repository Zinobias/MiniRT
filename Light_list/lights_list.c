/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lights_list.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 17:53:59 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/10/20 15:32:19 by zilisabethp   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	mlx_get_lights(t_data **mlx_, t_obj_list **list)
{
	t_obj_list	*current;
	t_data		*mlx;
	t_light_l	*current_l;

	current = *list;
	mlx = *mlx_;
	while (current)
	{
		if (current->obj_type->f_code == LIGHT)
		{
			if (!mlx->l_head)
			{
				create_light_head(&mlx, current->object.light);
				current_l = mlx->l_head;
			}
			else
			{
				while (current_l->next)
					current_l = current_l->next;
				create_light_node(&current_l, current->object.light);
			}
			current = rm_element(list, LIGHT);
		}
		current = current->next;
	}
}

void	create_light_head(t_data **target, t_light object)
{
	t_data		*current;

	current = *target;
	current->l_head = (t_light_l*)malloc(sizeof(t_light_l));
	if (!current->l_head)
		error("light head malloc went wrong", 29);
	current->l_head->light = object;
	current->l_head->next = NULL;
	return ;
}

void	create_light_node(t_light_l **target, t_light object)
{
	t_light_l	*current;

	current = *target;
	current->next = (t_light_l*)malloc(sizeof(t_light_l));
	if (!current->next)
		error("light node malloc went wrong", 29);
	current->next->light = object;
	current->next->next = NULL;
	return ;
}
