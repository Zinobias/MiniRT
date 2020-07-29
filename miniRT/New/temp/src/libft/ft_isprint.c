/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 16:22:51 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/06 11:59:08 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_isprint(int c)
{
	if (c >= ' ' && c <= '~')
		return (1);
	else
		return (0);
}