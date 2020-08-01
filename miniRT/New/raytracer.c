/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raytracer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 21:24:28 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/01 22:07:32 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	void	get_ray_nd(t_ray **ray, t_img_list *dest, double xx, double yy)
{
	(*ray)->dir = (t_vec3){xx, yy, -1};
	(*ray)->norm_dir = vec_normalize(&(*ray)->dir);
	(*ray)->norm_dir = setcam((*ray)->norm_dir, dest);
	(*ray)->norm_dir = vec_normalize(&(*ray)->norm_dir);
}

/*
** Calculating height image plane, width
** Getting ray dir/ nomr dir.
** checking for intersection.
** Calculating light.
*/

static void		ray_cast(t_ray **ray_, t_data **mlx,
	t_img_list *dest, t_obj_list **head)
{
	t_ray		*ray;
	int			xy[2];
	double		i_xy[2];

	ray = *ray_;
	xy[1] = 0;
	while (xy[1] < (*mlx)->res.y)
	{
		i_xy[1] = ((1 - 2 * ((xy[1] + 0.5) / ((*mlx)->res.y))) * ray->angle);
		xy[0] = 0;
		while (xy[0] < (*mlx)->res.x)
		{
			ray->orig = dest->cam_vals.view_p;
			i_xy[0] = ((2 * ((xy[0] + 0.5) / ((*mlx)->res.x)) - 1)
				* ray->angle * (*mlx)->aspect_ratio);
			get_ray_nd(&ray, dest, i_xy[0], i_xy[1]);
			check_hit(&ray, head);
			if (ray->hit.check == 1)
				check_light(&ray, *mlx, head);
			my_mlx_pixel_put(dest, *mlx, xy, ray->hit.color);
			xy[0]++;
		}
		xy[1]++;
	}
}

/*
** Calclating aspect ratio : width / height
** Calculating the right angle w/ fov
*/

void			render_(t_data **mlx_, t_obj_list **head, t_img_list *dest)
{
	t_data		*mlx;
	t_ray		*ray;
	int			xy[2];

	ray = (t_ray*)malloc(1 * sizeof(t_ray));
	if (!ray)
		error(MALLOC);
	xy[1] = 0;
	mlx = *mlx_;
	mlx->aspect_ratio = mlx->res.x / mlx->res.y;
	ray->angle = tan(M_PI * 0.5 * dest->cam_vals.fov / 180.);
	ray_cast(&ray, mlx_, dest, head);
	if (ray)
		free(ray);
	return ;
}

void			raytracer_(t_obj_list *list, int argc)
{
	t_data		*mlx;

	mlx_start(&mlx, &list);
	mlx_get_lights(&mlx, &list);
	mlx_get_cams(&mlx, &list);
	mlx_load_cams(&mlx, &list);
	if (argc == 3)
		save_img(mlx);
	else
	{
		link_cam_list(&mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img_l->img, 0, 0);
		mlx_hooks_(&mlx);
	}
	return ;
}

void			my_mlx_pixel_put(t_img_list *img_l, t_data *mlx,
int *xy, int color)
{
	char		*dst;

	dst = img_l->addr + (xy[1] * mlx->line_l + xy[0] * (mlx->bits_p_p / 8));
	*(unsigned int*)dst = color;
}
