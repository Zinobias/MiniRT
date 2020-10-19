/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 19:17:32 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/10/16 21:48:45 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			rgba(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int			get_r(int rgb)
{
	return ((rgb >> 16) & 255);
}

int			get_g(int rgb)
{
	return ((rgb >> 8) & 255);
}

int			get_b(int rgb)
{
	return ((rgb >> 0) & 255);
}
