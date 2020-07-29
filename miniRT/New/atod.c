/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   atod.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 17:19:13 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/06/24 16:37:15 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_atod_ret	ft_atod(char *str)
{
	t_atod_ret	ret;
	double		dec;
	int			d;

	d = 0;
	dec = 0;
	ret.i = *str == '-' ? 1 : 0;
	ret.val = 0;
	while (str[ret.i] >= '0' && str[ret.i] <= '9')
	{
		ret.val = ret.val * 10 + str[ret.i] - '0';
		ret.i++;
	}
	if (str[ret.i] == '.')
	{
		ret.i++;
		while (str[ret.i] >= '0' && str[ret.i] <= '9')
		{
			dec = dec * 10 + str[ret.i] - '0';
			d++;
			ret.i++;
		}
	}
	ret.val += dec * (1 / pow(10, d));
	ret.val = *str == '-' ? -ret.val : ret.val;
	return (ret);
}
