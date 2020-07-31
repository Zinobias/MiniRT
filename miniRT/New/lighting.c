/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 18:09:24 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/07/31 20:19:38 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	get_hit_point(t_ray **ray)
{
	t_vec3	hit_p;
	// t_vec3	bias;

	hit_p = vector_x_d(&(*ray)->norm_dir, (*ray)->hit.t1 - 10 * 1e-6);
	hit_p = vectorPlus(&(*ray)->orig, &hit_p);
	// add bias to hitpoint based on hit normal
	// bias = vector_x_d(&(*ray)->hit.hit_normal, - 10 * 1e-6);
	// hit_p = vectorPlus(&hit_p, &bias);
	return (hit_p);
}

// https://www.scratchapixel.com/code.php?id=13&origin=/lessons/3d-basic-rendering/introduction-to-shading

static t_colors	apply_light(t_ray *ray, t_light light, int temp, t_vec3 dist)
{
	t_colors	new;
	double		dotnormal;
	double		l_intensity;
	double		r2;

	// ray->hit.hit_normal = vec_normalize(&ray->hit.hit_normal);
	dotnormal = vectorDot(&ray->hit.hit_normal, &ray->norm_dir);
	if (dotnormal <= 1e-6)
		return ((t_colors){0,0,0});
	// l was ALBEDO
	r2 = vec3_pow(&dist);
	l_intensity = (light.brightness * dotnormal * 1000) / ( 4.0 * M_PI * r2);
	new = get_c_struct(temp);
	new = color_multiply(new , get_c_struct(light.colors), fmin(1.0, fmax(0.0, l_intensity)));
	return (new);
}

void	check_light(t_ray **ray, t_data *mlx, t_obj_list **list)
{
	t_vec3		hit_p;
	t_vec3		dist;
	t_colors	color;
	t_light_l	*current;

	current = mlx->l_head;
	// double	intensity;
	// apply ambient lighting
	color = color_multiply(get_c_struct((*ray)->hit.color), get_c_struct(mlx->ambient_light.colors), mlx->ambient_light.ratio);
	// calculate hit position of object.
	hit_p = get_hit_point(ray);
	// calculate the distance between the light and the hit point
	while (current)
	{
		dist = vectorSub(&current->t_light.light_p, &hit_p);
		// normalized direction from hitpoint to light
		(*ray)->norm_dir = vec_normalize(&dist);

		// (*ray)->orig = vector_x_d(&(*ray)->norm_dir, 1e-4);
		// (*ray)->orig = vectorPlus(&hit_p, &(*ray)->orig);
		(*ray)->orig = hit_p;
		// potentially shoot norm dir from lightsource rather than from hitpoint
		//  ray->normdir is now the vector towards the light source
		// check if there are any obstacles
		check_hit_l(ray, list, sqrt(vectorDot(&dist, &dist)));
		if ((*ray)->hit.check == 0)
			color = color_add(color, apply_light(*ray, current->t_light,
			(*ray)->hit.color, dist));
		color = (t_colors){fmin(color.r, 255), fmin(color.g, 255),
		fmin(color.b, 255)};
		(*ray)->hit.color = rgba(color.r, color.g, color.b, 0);
		current = current->next;
	}
	// hitColor += vis * isect.hitObject->albedo * lightIntensity * std::max(0.f, hitNormal.dotProduct(-lightDir)); 
	// L is now the distance between the light source and the hitpoint
	// so if any object is hit that is nor > nor < than l
	// means there should be a shadow.
	
}