/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 21:01:43 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/10/20 15:33:40 by zilisabethp   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	make_head(t_obj_list **head)
{
	t_obj_list	*new_head;

	new_head = (t_obj_list *)malloc(sizeof(t_obj_list));
	if (!new_head)
		error("Obj list_head malloc", 21);
	new_head->rac = 0;
	new_head->obj_type = NULL;
	new_head->next = NULL;
	*head = new_head;
	return ;
}

t_obj_list	*rm_element(t_obj_list **list, int obj_code)
{
	t_obj_list *current;
	t_obj_list *temp;

	current = *list;
	if (current->obj_type->f_code == obj_code)
	{
		if (current->next)
			*list = current->next;
		if (current)
			free(current);
	}
	else while (current->next)
	{
		if (current->next->obj_type->f_code == obj_code)
		{
			temp = current->next;
			if (temp)
				free(temp);
			current->next = current->next->next;
			break ;
		}
		current = current->next;
	}
	return (*list);
}
