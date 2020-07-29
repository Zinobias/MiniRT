/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 18:09:24 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/07/29 03:28:24 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_light(t_ray **ray, t_data *mlx, t_obj_list **list)
{
	t_vec3		hit_p;
	t_vec3		dist;
	t_colors	color;
	t_vec3		bias;
	double		l;
	// t_light_l	*current;
	// double	intensity;

	// apply ambient lighting
	color = get_c_struct((*ray)->hit.color);
	color_multiply(&color, get_c_struct(mlx->ambient_light.colors), mlx->ambient_light.ratio);
	// calculate hit position of object.	
	hit_p = vector_x_d(&(*ray)->norm_dir, (*ray)->hit.t1 - 10);
	hit_p = vectorPlus(&(*ray)->orig, &hit_p);
	// add bias to hitpoint based on hit normal
	bias = vector_x_d(&(*ray)->hit.hit_normal, 10 * 1e-6);
	hit_p = vectorPlus(&hit_p, &bias);

	// calculate the distance between the light and the hit point
	dist = vectorSub(&mlx->l_head->t_light.light_p, &hit_p);
	// normalized direction from hitpoint to light
	(*ray)->norm_dir = vec_normalize(&dist);

	// (*ray)->orig = vector_x_d(&(*ray)->norm_dir, 1e-4);
	// (*ray)->orig = vectorPlus(&hit_p, &(*ray)->orig);
	(*ray)->orig = hit_p;
	// potentially shoot norm dir from lightsource rather than from hitpoint
	//  ray->normdir is now the vector towards the light source
	l = sqrt(vectorDot(&dist, &dist));
	
	// check if there are any obstacles
	check_hit_l(ray, list, l);

	if ((*ray)->hit.check == 0)
		color_add(&color, apply_light(*ray, mlx->l_head->t_light));
	color = (t_colors){fmin(color.r, 255), fmin(color.g, 255), fmin(color.b, 255)};
	(*ray)->hit.color = rgba(color.r, color.g, color.b, 0);
	// hitColor += vis * isect.hitObject->albedo * lightIntensity * std::max(0.f, hitNormal.dotProduct(-lightDir)); 
	// L is now the distance between the light source and the hitpoint
	// so if any object is hit that is nor > nor < than l
	// means there should be a shadow.
	
}