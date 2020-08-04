/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   img_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 17:51:17 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/04 18:06:34 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cam_head(t_data **mlx_data, t_cam vals)
{
	t_data *mlx;

	mlx = *mlx_data;
	mlx->img_l = (t_img_list*)malloc(sizeof(t_img_list));
	if (!mlx->img_l)
		error("MALLOC, IMG_L", 14);
	mlx->img_l->cam = 1;
	mlx->img_l->next = NULL;
	mlx->img_l->back = NULL;
	mlx->img_l->addr = NULL;
	mlx->img_l->img = NULL;
	mlx->img_l->img = mlx_new_image(mlx->mlx, mlx->res.x, mlx->res.y);
	if (!mlx->img_l->img)
		error("MLX IMG creation boohoo", 24);
	mlx->img_l->addr = mlx_get_data_addr(mlx->img_l->img,
		&mlx->bits_p_p, &mlx->line_l, &mlx->endian);
	if (!mlx->img_l->addr)
		error("MLX get addr of img, booho", 27);
	mlx->img_l->cam_vals = vals;
	return ;
}

void	create_cam_node(t_img_list **img_l, t_data **mlx_data, t_cam vals)
{
	int			temp;
	t_img_list	*current;
	t_data		*mlx;

	mlx = *mlx_data;
	current = *img_l;
	temp = current->cam;
	current->next = (t_img_list*)malloc(1 * sizeof(t_img_list));
	if (!current->next)
		error("MALLOC in camnode boo", 22);
	current->next->cam = temp + 1;
	current->next->back = current;
	current->next->next = NULL;
	current->next->back = NULL;
	current->next->addr = NULL;
	current->next->img = NULL;
	current->next->img = mlx_new_image(mlx->mlx, mlx->res.x, mlx->res.y);
	if (!current->next->img)
		error("MLX error, new img, create node", 32);
	current->next->addr = mlx_get_data_addr(current->next->img,
		&mlx->bits_p_p, &mlx->line_l, &mlx->endian);
	if (!current->next->addr)
		error("Getting img address went wrong", 31);
	current->next->cam_vals = vals;
	return ;
}

void	mlx_get_cams(t_data **mlx_data, t_obj_list **obj_l)
{
	t_data		*mlx;
	t_obj_list	*current;
	t_img_list	*current_i;

	mlx = *mlx_data;
	current = *obj_l;
	while (current)
	{
		if (current->obj_type->f_code == CAM)
		{
			if (!mlx->img_l)
			{
				cam_head(&mlx, current->object.cam);
				current_i = mlx->img_l;
			}
			else
			{
				while (current_i->next)
					current_i = current_i->next;
				create_cam_node(&current_i, mlx_data, current->object.cam);
			}
			rm_element(obj_l, CAM);
		}
		current = current->next;
	}
}

void	link_cam_list(t_data **mlx_)
{
	t_img_list	*current;
	t_img_list	*temp;
	t_data		*mlx;

	mlx = *mlx_;
	current = mlx->img_l;
	mlx->img_tail = NULL;
	if (!(current->next))
		return ;
	while (current->next)
	{
		temp = current;
		current = current->next;
		current->back = temp;
	}
	mlx->img_tail = current;
}
