/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 21:06:32 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/01 21:33:06 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_f3_ret		get_fields(char *line)
{
	t_f3_ret	data;
	t_atod_ret	atod_ret;

	data.fields = 0;
	data.i = 0;
	while (line[data.i] == ' ' && line[data.i])
		data.i++;
	while ((line[data.i] >= '0' && line[data.i] <= '9') || line[data.i] == '-')
	{
		atod_ret = ft_atod(line + data.i);
		data.i += atod_ret.i;
		data.f_info.x = data.fields == 0 ? atod_ret.val : data.f_info.x;
		data.f_info.y = data.fields == 1 ? atod_ret.val : data.f_info.y;
		data.f_info.z = data.fields == 2 ? atod_ret.val : data.f_info.z;
		data.fields++;
		data.i += line[data.i] == ',' && data.fields != 3 ? 1 : 0;
	}
	if (data.fields != 3 && (line[data.i] == ' ' || line[data.i] == '\0'))
		error(INVAL);
	return (data);
}

t_d_ret			get_double(char *line)
{
	t_d_ret		ret;
	t_atod_ret	atod_data;

	ret.val = 0;
	ret.i = 0;
	while (line[ret.i] == ' ')
		ret.i++;
	if (line[ret.i] >= '0' || line[ret.i] <= '9' || line[ret.i] == '-')
	{
		atod_data = ft_atod(line + ret.i);
		ret.val = atod_data.val;
		ret.i += atod_data.i;
		ret.i++;
	}
	else if ((line[ret.i] >= '0' || line[ret.i] <= '9')
	|| line[ret.i] != ' ')
		error(INVAL);
	return (ret);
}

t_i_ret			get_int(char *line)
{
	t_i_ret		ret;
	t_atod_ret	atod_data;

	ret.val = 0;
	ret.i = 0;
	while (line[ret.i] == ' ')
		ret.i++;
	if ((line[ret.i] >= '0' && line[ret.i] <= '9') || line[ret.i] == '-')
	{
		atod_data = ft_atod(line + ret.i);
		ret.val = atod_data.val;
		ret.i += atod_data.i;
	}
	else
		error(INVAL);
	return (ret);
}
