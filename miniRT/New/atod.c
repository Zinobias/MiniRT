/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   atod.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 17:19:13 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/01 16:34:41 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_atod_ret	ft_atod(char *str)
{
	t_atod_ret	ret;
	double		dec[2];

	dec[1] = 0;
	dec[0] = 0;
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
			dec[0] = dec[0] * 10 + str[ret.i] - '0';
			dec[1]++;
			ret.i++;
		}
	}
	ret.val += dec[0] * (1 / pow(10, dec[1]));
	ret.val = *str == '-' ? -ret.val : ret.val;
	return (ret);
}
