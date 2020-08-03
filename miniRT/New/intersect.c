/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/12 16:47:31 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/04 00:09:29 by zgargasc      ########   odam.nl         */
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

void	check_hit(t_ray **ray, t_obj_list **head)
{
	t_obj_list		*current;
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
				break ;
			}
			i++;
		}
		current = current->next;
	}
}

void	check_hit_l(t_ray **ray, t_obj_list **head, double l)
{
	t_light_hit_info	i;

	i.current = *head;
	(*ray)->hit.t1 = INFINITY;
	(*ray)->hit.check = 0;
	while (i.current)
	{
		i.i = 0;
		while (i.i < 5)
		{
			i.current_f = &g_f_array_int[i.i];
			if (i.current_f->f_code == i.current->obj_type->f_code)
			{
				i.hit = (*g_f_array_int[i.i].function)(*ray, i.current->object);
				if (i.hit.check == 1 && (i.hit.t1 < l && i.hit.t1 > 0))
				{
					(*ray)->hit.check = 1;
					return ;
				}
				break ;
			}
			i.i++;
		}
		i.current = i.current->next;
	}
}
