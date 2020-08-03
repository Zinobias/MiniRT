/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quad_solve.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 16:28:03 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/04 00:25:40 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	quad_solve(double *res, t_hit *hit)
{
	double	disc;
	double	q;

	disc = (res[1] * res[1]) - 4.0 * res[0] * res[2];
	if (disc < 1e-6)
	{
		hit->check = INFINITY;
		return ;
	}
	else if (disc == 0.)
	{
		hit->t1 = -0.5 * res[1] / res[0];
		hit->t2 = hit->t1;
	}
	else
	{
		q = (res[1] > 0) ? -0.5 * (res[1] + sqrt(disc)) :
		-0.5 * (res[1] - sqrt(disc));
		hit->t1 = q / res[0];
		hit->t2 = res[2] / q;
	}
	hit->check = 2;
	return ;
}
