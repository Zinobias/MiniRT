/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 19:17:32 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/05 17:47:48 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			rgba(int r, int g, int b, int t)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int			get_t(int trgb)
{
	return ((trgb >> 24) & 255);
}

int			get_r(int trgb)
{
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
