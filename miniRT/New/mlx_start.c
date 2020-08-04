/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_start.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 21:28:04 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/04 18:16:57 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	mlx_start(t_data **mlx_data, t_obj_list **list)
{
	t_data *mlx;

	if (!((*list)->rac & 4))
		error("Missing cam", 12);
	mlx = (t_data*)malloc(sizeof(t_data));
	if (!mlx)
		error("Mallocing mlx struct went wrong", 32);
	*mlx_data = mlx;
	l_get_r(mlx_data, list);
	l_get_a(mlx_data, list);
	mlx->mlx = mlx_init();
	mlx->img_l = NULL;
	mlx->l_head = NULL;
	if (!mlx->mlx)
		error("mlx init went wrong", 20);
	mlx->win = mlx_new_window(mlx->mlx, mlx->res.x, mlx->res.y,
		"Headache_generator_9000");
	if (!mlx->win)
		error("making mlx window went wrong", 29);
	return ;
}

void	mlx_load_cams(t_data **mlx_data, t_obj_list **head)
{
	t_img_list	*current;
	t_data		*mlx;

	mlx = *mlx_data;
	current = mlx->img_l;
	while (current)
	{
		render_(mlx_data, head, current);
		current = current->next;
	}
	return ;
}
