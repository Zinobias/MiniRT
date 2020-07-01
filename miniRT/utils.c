/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 18:35:54 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/07/01 17:56:35 by zgargasc      ########   odam.nl         */
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
	t_img_list	*temp;

	if (keycode == 53)
	{
		while (mlx->img_l)
		{
			if (mlx->img_l->next)
				temp = mlx->img_l->next;
			mlx_destroy_image(mlx->mlx, mlx->img_l->img);
			mlx->img_l = temp;
		}
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return (0);
}

int		close_win_x(t_data *mlx)
{
	t_img_list	*temp;

	while (mlx->img_l)
	{
		if (mlx->img_l->next)
			temp = mlx->img_l->next;
		mlx_destroy_image(mlx->mlx, mlx->img_l->img);
		mlx->img_l = temp;
	}
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (0);
}

t_amb	l_get_A(t_obj_list **list)
{
	t_obj_list	*current;

	current = *list;
	if (current->obj_type->f_code == AMB)
	{
		rm_element(list, AMB);
		return(current->object.amb);
	}
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
	{
		rm_element(list, RES);
		return(current->object.res);
	}
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
		current = current->next;
	}
	return ;
}

void cam_head(t_data **mlx_data, t_cam vals)
{
	t_data *mlx;

	mlx = *mlx_data;
	mlx->img_l = (t_img_list*)malloc(sizeof(t_img_list));
	if (!mlx->img_l)
		error(MALLOC);
	mlx->img_l->cam = 1;
	mlx->img_l->next = NULL;
	mlx->img_l->back = NULL;
	mlx->img_l->addr = NULL;
	mlx->img_l->img = NULL;
	mlx->img_l->img = mlx_new_image(mlx->mlx, mlx->res.x, mlx->res.y);
	if (!mlx->img_l->img)
		error(MLX);
	mlx->img_l->addr =	mlx_get_data_addr(mlx->img_l->img, &mlx->bits_p_p, &mlx->line_l, &mlx->endian);
	if (!mlx->img_l->addr)
		error(MLX);
	mlx->img_l->cam_vals = vals;
	return ;
}

void create_cam_node(t_img_list **img_l, t_data **mlx_data, t_cam vals)
{
	int			temp;
	t_img_list *current;
	t_data *mlx;

	mlx = *mlx_data;
	current = *img_l;
	temp = current->cam;
	current->next = (t_img_list*)malloc(sizeof(t_img_list));
	if (!current->next)
		error(MALLOC);
	current->next->cam = temp + 1;
	current->next->back = current;
	current->next->next = NULL;
	current->next->back = NULL;
	current->next->addr = NULL;
	current->next->img = NULL;
	current->next->img = mlx_new_image(mlx->mlx, mlx->res.x, mlx->res.y);
	if (!current->next->img)
		error(MLX);
	current->next->addr =	mlx_get_data_addr(current->next->img, &mlx->bits_p_p, &mlx->line_l, &mlx->endian);
	if (!current->next->addr)
		error(MLX);
	current->next->cam_vals = vals;
	return ;
}

void mlx_get_cams(t_data **mlx_data, t_obj_list **obj_l)
{
	t_data 		*mlx;
	t_obj_list 	*current;
	
	mlx = *mlx_data;
	current = *obj_l;
	while (current)
	{
	
		if (current->obj_type->f_code == CAM)
		{
			if (!mlx->img_l)
				cam_head(&mlx, current->object.cam);
			else while (mlx->img_l->next)
			{
				create_cam_node(&mlx->img_l, mlx_data, current->object.cam);
				mlx->img_l = mlx->img_l->next;
			}
			rm_element(obj_l, CAM);
		}
		current = current->next;
	}
	// potentially rm node right away, and store temp, rather than using rm_element.
	// for optimizing.
	return ;
}

void	mlx_hooks_(t_data **mlx_)
{
	t_data *mlx;

	mlx = *mlx_;
	mlx_key_hook(mlx->win, close_window_esc, mlx);
	mlx_hook(mlx->win, 17, 0, close_win_x, mlx);
	mlx_loop(mlx->mlx);
	return ;
}

float	vec_normalize(t_vec3 vec3, float N)
{
	return((vec3.x / N) + (vec3.y / N) + (vec3.z / N));
}

t_vec3 vectorSub(t_vec3 *v1, t_vec3 *v2)
{
	return (vec3(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z));
}

float vectorDot(t_vec3 *v1, t_vec3 *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vec3 vectorMin(t_vec3 *v1, t_vec3 *v2)
{
	return (vec3(v1->x - v2->x,  v1->y - v2->y, v1->z - v2->z));
}

t_vec3 vectorPlus(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	res;

	res.x = v1->x + v2->x; 
	res.y = v1->y + v2->y;
	res.z =	v1->z + v2->z;
	return (res);
}