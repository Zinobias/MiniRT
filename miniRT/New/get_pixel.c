/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_pixel.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 17:56:06 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/01 21:08:06 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_colors	get_pixel(t_data *mlx, int x, int y)
{
	unsigned		i;
	unsigned int	color;
	t_colors		col;

	i = y * mlx->line_l + x * (mlx->bits_p_p / 8);
	color = *(unsigned int*)(mlx->img_l->addr + i);
	col = get_c_struct(color);
	return (col);
}
