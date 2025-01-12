/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_structs.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 16:23:34 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/10/17 16:16:03 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_colors	get_c_struct(int color)
{
	t_colors	new;

	new = (t_colors){get_r(color), get_g(color), get_b(color)};
	return (new);
}

t_colors	color_multiply(t_colors c1, t_colors c2, double s)
{
	c1.r *= (c2.r * s / 255);
	c1.g *= (c2.g * s / 255);
	c1.b *= (c2.b * s / 255);
	return (c1);
}

t_colors	color_x_double(t_colors *c1, double d)
{
	c1->r *= d;
	c1->g *= d;
	c1->b *= d;
	return (*c1);
}

t_colors	color_add(t_colors c1, t_colors c2)
{
	c1.r += c2.r;
	c1.g += c2.g;
	c1.b += c2.b;
	return (c1);
}
