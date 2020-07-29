/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ndc.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 11:43:32 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/13 13:33:30 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

double		get_ndcx_pos(t_base *b, int x)
{
	double	ratio;
	double	angle;
	double	ndc_x;

	ratio = b->res.x_max / b->res.y_max;
	ndc_x = (x + 0.5) / b->res.x_max;
	ndc_x = 2 * ndc_x - 1;
	angle = b->cam.c[b->i_c].fov / 2 * M_PI / 180;
	ndc_x *= ratio * tan(angle);
	return (ndc_x);
}

double		get_ndcy_pos(t_base *b, int y)
{
	double	angle;
	double	ndc_y;

	ndc_y = (y + 0.5) / b->res.x_max;
	ndc_y = 1 - 2 * ndc_y;
	angle = b->cam.c[b->i_c].fov / 2 * M_PI / 180;
	ndc_y *= tan(angle);
	return (ndc_y);
}
