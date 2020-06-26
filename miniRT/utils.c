/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 18:35:54 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/06/26 10:46:28 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3(int x, int y, int z)
{
	t_vec3	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vec2	vec2(int x, int y)
{
	t_vec2	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

void	check_vec3_range(t_vec3 data, double min, double max)
{
	if ((data.x > max || data.y > max || data.z > max)
	|| (data.x < min || data.y < min || data.z < min))
		error(INVAL);
}

void	check_line_valid(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			error(INVAL);
		i++;
	}
	return ;
}

void	make_head(t_obj_list **head)
{
	t_obj_list	*new_head;

	new_head = (t_obj_list *)malloc(sizeof(t_obj_list));
	if (!new_head)
		error(MALLOC);
	new_head->rac = 0;
	new_head->obj_type = NULL;
	new_head->next = NULL;
	*head = new_head;
	return ;
}

void	error(int code)
{
	if (code == INVAL)
		write(1, "ERROR\nINVALID SCENE", 20);
	if (code == MALLOC)
		write(1, "ERROR\nMALLOC", 13);
	if (code == GNL)
		write(1, "ERROR\nGET_NEXT_LINE", 20);
	if (code == MLX)
		write(1, "ERROR\nMLX", 10);
	exit(1);
}

int	close_window_esc(int keycode, t_data *mlx)
{
	if (keycode == 53)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return (0);
}

int		close_win_x(t_data *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (0);
}

t_amb	l_get_A(t_obj_list **list)
{
	t_obj_list	*current;

	current = *list;
	if (current->obj_type->f_code == AMB)
		return(current->object.amb);
	else while (current->next)
	{
		if (current->obj_type->f_code == AMB)
			break;
		current = current->next;
	}
	rm_element(list, AMB);
	return (current->object.amb);
}

t_res	l_get_R(t_obj_list **list)
{
	t_obj_list	*current;

	current = *list;
	if (current->obj_type->f_code == RES)
		return(current->object.res);
	else while (current->next)
	{
		if (current->obj_type->f_code == RES)
			break;
		current = current->next;
	}
	rm_element(list, RES);
	return (current->object.res);
}

void	rm_element(t_obj_list **list, int obj_code)
{
	t_obj_list *current;
	t_obj_list *temp;

	current = *list;
	if (current->obj_type->f_code == obj_code)
	{
		if (current->next)
			*list = current->next;
		free(current);
	}
	else while (current->next)
	{
		if (current->next->obj_type->f_code == obj_code)
		{
			temp = current->next;
			current = current->next->next;
			free(temp);
			break;
		}
		current->next = current->next;
	}

	// check if exit properly frees this
	return ;
}