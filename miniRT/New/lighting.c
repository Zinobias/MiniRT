/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pani_zino <pani_zino@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/02 00:14:26 by pani_zino     #+#    #+#                 */
/*   Updated: 2020/08/03 18:10:34 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** - 10 * 1e-6 to add bias.
** https://www.scratchapixel.com/code.php?id=13&origin=
** /lessons/3d-basic-rendering/introduction-to-shading
*/

static t_vec3		get_hit_point(t_ray **ray)
{
	t_vec3		hit_p;

	hit_p = vector_x_d(&(*ray)->norm_dir, (*ray)->hit.t1 - 10 * 1e-6);
	hit_p = vector_plus(&(*ray)->orig, &hit_p);
	return (hit_p);
}

static t_colors		apply_light(t_ray *ray, t_light light,
									int temp, t_vec3 dist)
{
	t_colors	new;
	double		dotnormal;
	double		l_intensity;
	double		r2;

	dotnormal = vector_dot(&ray->hit.hit_normal, &ray->norm_dir);
	if (dotnormal <= 1e-6)
		dotnormal = fabs(dotnormal);
	r2 = vec3_pow(&dist);
	l_intensity = (light.brightness * dotnormal * 1000) / (4.0 * M_PI * r2);
	new = get_c_struct(temp);
	new = color_multiply(new, get_c_struct(light.colors),
		fmin(1.0, fmax(0.0, l_intensity)));
	return (new);
}

/*
** apply ambient lighting
** calculate hit position of object.
** calculate the distance between the light and the hit point
** normalized direction from hitpoint to light
** (*ray)->orig = vector_x_d(&(*ray)->norm_dir, 1e-4);
** (*ray)->orig = vector_plus(&hit_p, &(*ray)->orig);
** check if there are any obstacles
*/
/*
** hitColor += vis * isect.hitObject->albedo *
** lightIntensity * std::max(0.f, hitNormal.dotProduct(-lightDir));
** L is now the distance between the light source and the hitpoint
** so if any object is hit that is nor > nor < than l
** means there should be a shadow.
*/

void				check_light(t_ray **ray, t_data *mlx, t_obj_list **list)
{
	t_vec3		hit_p;
	t_vec3		dist;
	t_colors	color;
	t_light_l	*current;


	// add ft_calloc
	color = color_multiply(get_c_struct((*ray)->hit.color),
		get_c_struct(mlx->ambient_light.colors), mlx->ambient_light.ratio);
	hit_p = get_hit_point(ray);
	current = mlx->l_head;
	while (current)
	{
		dist = vector_sub(&current->light.light_p, &hit_p);
		(*ray)->norm_dir = vec_normalize(&dist);
		(*ray)->orig = hit_p;
		check_hit_l(ray, list, sqrt(vector_dot(&dist, &dist) - 1e-6));
		if ((*ray)->hit.check == 0)
			color = color_add(color, apply_light(*ray, current->light,
				(*ray)->hit.color, dist));
		current = current->next;
	}
	color = (t_colors){fmin(color.r, 255), fmin(color.g, 255),
	fmin(color.b, 255)};
	(*ray)->hit.color = rgba(color.r, color.g, color.b, 0);
}
