/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 19:17:32 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/10/10 21:32:38 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			rgba(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
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
