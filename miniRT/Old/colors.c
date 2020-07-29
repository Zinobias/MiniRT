/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 19:17:32 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/07/22 14:44:40 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			rgba(int r, int g, int b, int t)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int			get_t(int trgb)
{
	return (trgb & 0xFF);
}

int			get_r(int trgb)
{
	return (trgb & 0xFF00);
}

int			get_g(int trgb)
{
	return (trgb & 0xFF0000);
}

int			get_b(int trgb)
{
	return (trgb & 0xFF000000);
}

