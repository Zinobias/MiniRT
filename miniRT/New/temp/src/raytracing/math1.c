/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math1.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 15:21:58 by ldideric      #+#    #+#                 */
/*   Updated: 2020/06/11 15:27:17 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

t_vect		vec3(double x, double y, double z)
{
	t_vect new;

	new.x = x;
	new.y = y;
	new.z = z;
	new.hit = 0;
	return (new);
}

t_vect		ft_normalize(t_vect a)
{
	double w;

	w = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	a.x /= w;
	a.y /= w;
	a.z /= w;
	return (a);
}

t_vect		vect_min(t_vect a, t_vect b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

t_vect		vect_plus(t_vect a, t_vect b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

t_vect		cross_pr(t_vect a, t_vect b)
{
	t_vect new;

	new.x = (a.y * b.z) - (a.z * b.y);
	new.y = (a.z * b.x) - (a.x * b.z);
	new.z = (a.x * b.y) - (a.y * b.x);
	return (new);
}

double		dot(t_vect a, t_vect b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

double		length(t_vect a)
{
	return (sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2)));
}

double		length_betw(t_vect a, t_vect b)
{
	return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2)));
}
