/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 17:54:26 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/10/17 16:36:58 by zgargasc      ########   odam.nl         */
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

static t_colors		apply_light(t_ray *ray, t_light light, t_l_pass l_p)
{
	t_colors	new;
	double		shade;
	double		l_intensity;

	shade = vector_dot(&ray->hit.hit_normal, &ray->norm_dir);
	if (shade <= 1e-6 && (ray->hit.obj_type == PL
								|| ray->hit.obj_type == TR))
		shade = fabs(shade);
	if (shade < 1e-6)
		return ((t_colors){0, 0, 0});
	l_intensity = light.brightness * fmax(0, shade) * (1 - l_p.amb_b);
	new = get_c_struct(light.colors);
	new = color_x_double(&new, l_intensity);
	return ((t_colors){fmin(new.r, 255), fmin(new.g, 255), fmin(new.b, 255)});
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
	t_l_pass	l_p;
	t_colors	color;
	t_light_l	*current;

	l_p.amb_b = mlx->ambient_light.ratio;
	color = color_multiply(get_c_struct((*ray)->hit.color),
		get_c_struct(mlx->ambient_light.colors), mlx->ambient_light.ratio);
	hit_p = get_hit_point(ray);
	current = mlx->l_head;
	while (current)
	{
		l_p.dist = vector_sub(&current->light.light_p, &hit_p);
		(*ray)->norm_dir = vec_normalize(&l_p.dist);
		(*ray)->orig = hit_p;
		check_hit_l(ray, list, sqrt(vector_dot(&l_p.dist,
			&l_p.dist) - 10 * 1e-6));
		if ((*ray)->hit.check == 0)
			color = color_add(color, apply_light(*ray, current->light,
				l_p));
		current = current->next;
	}
	color = (t_colors){fmin(color.r, 255), fmin(color.g, 255),
	fmin(color.b, 255)};
	(*ray)->hit.color = rgba(color.r, color.g, color.b);
}
