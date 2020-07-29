/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 19:17:32 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/07/29 05:02:22 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rgba(int r, int g, int b, int t)
{
	int color;

	color = 0;
	color = t << 24 | r << 16 | g << 8 | b;
	return ((unsigned int) color);
}


int			get_t(int trgb)
{
	return ((trgb >> 24) & 255);
}

int			get_r(int trgb)
{
	// return (trgb & 0xFF0000);
	return ((trgb >> 16) & 255);
}

int			get_g(int trgb)
{
	return ((trgb >> 8) & 255);
}

int			get_b(int trgb)
{
	return (trgb & 255);
}
// int			get_t(int trgb)
// {
// 	return (trgb & 0xFF000000);
// }

// int			get_r(int trgb)
// {
// 	// return (trgb & 0xFF0000);
// 	return (trgb >> 16);
// }

// int			get_g(int trgb)
// {
// 	return (trgb & 0xFF00);
// }

// int			get_b(int trgb)
// {
// 	return (trgb & 0xFF);
// }

t_colors	get_c_struct(int color)
{
	t_colors	new;

	new = (t_colors){get_r(color), get_g(color), get_b(color)};
	return (new);
}
void	color_multiply(t_colors *c1, t_colors c2, double s)
{
	c1->r *= (c2.r * s / 255);
	c1->g *= (c2.g * s / 255);
	c1->b *= (c2.b * s / 255);
}

void	color_add(t_colors *c1, t_colors c2)
{
	c1->r += c2.r;
	c1->g += c2.g;
	c1->b += c2.b;
}
