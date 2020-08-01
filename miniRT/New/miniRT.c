/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 21:29:41 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/01 13:54:15 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// How to read a plane. // line of sight
// Calculation from plane to square.
// Camera 
// calculation from plane to X.
// Camera rotations
// shadows.
// Fresnel equation for glass. & whitted algorithm
// Backwards tracing.
// Light tracing / light or shadow ray if obstructed = shadow
//  first ray = primary / visibility / camera  --- ray
// shooting rays from the light or eye = path tracing. / ray tracing

// //  Pseudo code :
// for (int j = 0; j < imageHeight; ++j) { 
//     for (int i = 0; i < imageWidth; ++i) { 
//         // compute primary ray direction
//         Ray primRay; 
//         computePrimRay(i, j, &primRay); 
//         // shoot prim ray in the scene and search for intersection
//         Point pHit; 
//         Normal nHit; 
//         float minDist = INFINITY; 
//         Object object = NULL; 
//         for (int k = 0; k < objects.size(); ++k) { 
//             if (Intersect(objects[k], primRay, &pHit, &nHit)) { 
//                 float distance = Distance(eyePosition, pHit); 
//                 if (distance < minDistance) { 
//                     object = objects[k]; 
//                     minDistance = distance; // update min distance 
//                 } 
//             } 
//         } 
//         if (object != NULL) { 
//             // compute illumination
//             Ray shadowRay; 
//             shadowRay.direction = lightPosition - pHit; 
//             bool isShadow = false; 
//             for (int k = 0; k < objects.size(); ++k) { 
//                 if (Intersect(objects[k], shadowRay)) { 
//                     isInShadow = true; 
//                     break; 
//                 } 
//             } 
//         } 
//         if (!isInShadow) 
//             pixels[i][j] = object->color * light.brightness; 
//         else 
//             pixels[i][j] = 0; 
//     } 
// } 

// Pseudo code fresnel algorithm
// // compute reflection color 
// color reflectionCol = computeReflectionColor(); 
// // compute refraction color
// color refractionCol = computeRefractionColor(); 
// float Kr; // reflection mix value 
// float Kt; // refraction mix value 
// fresnel(refractiveIndex, normalHit, primaryRayDirection, &Kr, &Kt); 
// // mix the two
// color glassBallColorAtHit = Kr * reflectionColor + (1-Kr) * refractionColor; 
// compute reflection color
// color reflectionCol = computeReflectionColor(); 
// // compute refraction color
// color refractionCol = computeRefractionColor(); 
// float Kr; // reflection mix value 
// float Kt; // refraction mix value 
// fresnel(refractiveIndex, normalHit, primaryRayDirection, &Kr, &Kt); 
// // mix the two
// color glassBallColorAtHit = Kr * reflectionColor + (1-Kr) * refractionColor; 

// recursive RT function pseudo code 
// #define MAX_RAY_DEPTH 3 
 
// color Trace(const Ray &ray, int depth) 
// { 
//     Object *object = NULL; 
//     float minDist = INFINITY; 
//     Point pHit; 
//     Normal nHit; 
//     for (int k = 0; k < objects.size(); ++k) { 
//         if (Intersect(objects[k], ray, &pHit, &nHit)) { 
//             // ray origin = eye position of it's the prim ray
//             float distance = Distance(ray.origin, pHit); 
//             if (distance < minDistance) { 
//                 object = objects[i]; 
//                 minDistance = distance; 
//             } 
//         } 
//     } 
//     if (object == NULL) 
//         return 0; 
//     // if the object material is glass, split the ray into a reflection
//     // and a refraction ray.
//     if (object->isGlass && depth < MAX_RAY_DEPTH) { 
//         // compute reflection
//         Ray reflectionRay; 
//         reflectionRay = computeReflectionRay(ray.direction, nHit); 
//         // recurse
//         color reflectionColor = Trace(reflectionRay, depth + 1); 
//         Ray refractioRay; 
//         refractionRay = computeRefractionRay( 
//             object->indexOfRefraction, 
//             ray.direction, 
//             nHit); 
//         // recurse
//         color refractionColor = Trace(refractionRay, depth + 1); 
//         float Kr, Kt; 
//         fresnel( 
//             object->indexOfRefraction, 
//             nHit, 
//             ray.direction, 
//             &Kr, 
//             &Kt); 
//         return reflectionColor * Kr + refractionColor * (1-Kr); 
//     } 
//     // object is a diffuse opaque object        
//     // compute illumination
//     Ray shadowRay; 
//     shadowRay.direction = lightPosition - pHit; 
//     bool isShadow = false; 
//     for (int k = 0; k < objects.size(); ++k) { 
//         if (Intersect(objects[k], shadowRay)) { 
//             // hit point is in shadow so just return
//             return 0; 
//         } 
//     } 
//     // point is illuminated
//     return object->color * light.brightness; 
// } 

#include "minirt.h"

void	check_string(char *s)
{
	int					i;
	static const char 	*example = "--save";
	
	i = 0;
	while (i < 7)
	{
		if (s[i] != example[i])
			error(INVAL_I);
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_obj_list *list;
	int			fd;

	if (argc != 2 && argc != 3)
		error(INVAL_I);
	if (argc == 3)
		check_string(argv[2]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error(OPEN_CLOSE_WRITE);
	list = parser(fd);
	if (close(fd) == -1)
		error(OPEN_CLOSE_WRITE);
	raytracer_(list, argc);
	exit(0);
	return (0);
}

void	mlx_start(t_data **mlx_data, t_obj_list **list)
{
	t_data *mlx;

	if (!((*list)->rac & 4))
		error(INVAL);
	mlx = (t_data*)malloc(sizeof(t_data));
	if (!mlx)
		error(MALLOC);
	*mlx_data = mlx;
	l_get_R(mlx_data, list);
	l_get_A(mlx_data, list);
	mlx->mlx = mlx_init();
	mlx->img_l = NULL;
	mlx->l_head = NULL;
	if (!mlx->mlx)
		error(MLX);
	mlx->win = mlx_new_window(mlx->mlx, mlx->res.x, mlx->res.y, "Headache_generator_9000");
	if (!mlx->win)
		error(MLX);
	return ;
}
static	void	get_ray_nd(t_ray **ray, t_img_list *dest, double xx, double yy)
{
		(*ray)->dir = (t_vec3){xx, yy, -1};
			// normalizing ray_dir
		(*ray)->norm_dir = vec_normalize(&(*ray)->dir);
		(*ray)->norm_dir = setcam((*ray)->norm_dir, dest);
		(*ray)->norm_dir = vec_normalize(&(*ray)->norm_dir);
}

static void		ray_cast(t_ray **ray_, t_data **mlx_data, t_img_list *dest, t_obj_list **head)
{
	t_data	*mlx;
	t_ray	*ray;
	int		xy[2];
	double	i_xy[2];

	mlx = *mlx_data;
	ray = *ray_;
	xy[1] = 0;
	while (xy[1] < mlx->res.y)
	{
		i_xy[1] = ((1 - 2 * ((xy[1] + 0.5) / (mlx->res.y))) * ray->angle);
		xy[0] = 0;
		// calculating height image plane
		while (xy[0] < mlx->res.x)
		{
			ray->orig = dest->cam_vals.view_p;
			i_xy[0] = ((2 * ((xy[0] + 0.5) / (mlx->res.x)) - 1) * ray->angle * mlx->aspect_ratio);
			// calculating width image plane
			get_ray_nd(&ray, dest, i_xy[0], i_xy[1]);
			// ray dir
			// // normalizing ray_dir
			check_hit(&ray, head);
			if (ray->hit.check == 1)
				check_light(&ray, mlx, head);
			my_mlx_pixel_put(dest, mlx, xy[0], xy[1], ray->hit.color);
			xy[0]++;
		}
		xy[1]++;
	}
}

void	render_(t_data **mlx_, t_obj_list **head, t_img_list *dest)
{
	t_data 	*mlx;
	t_ray	*ray;
	int		xy[2];

	ray = (t_ray*)malloc(1 * sizeof(t_ray));
	if (!ray)
		error(MALLOC);
	xy[1] = 0;
	mlx = *mlx_;
	// calculating aspecct ratio, width / height.
	mlx->aspect_ratio = mlx->res.x / mlx->res.y;
	// calculating right angle fov
	ray->angle = tan(M_PI * 0.5 * dest->cam_vals.fov / 180.);
	ray_cast(&ray, mlx_, dest, head);
	if (ray)
		free(ray);
	return ;
}

// This example of the video seems bad https://www.youtube.com/watch?v=LRN_ewuN_k4
// Forward = target - origin
// Right = Forward x Upguide
// Up = Right x Forward




void	mlx_load_cams(t_data **mlx_data, t_obj_list **head)
{
	t_img_list 	*current;
	t_data		*mlx;
	
	mlx = *mlx_data;
	current = mlx->img_l;
	while (current)
	{
		printf("Fov : %f\n", current->cam_vals.fov);
		printf("Cam : [%i]\n", current->cam);
		render_(mlx_data, head, current);
		current = current->next;
	}
	return ;
}

void	link_cam_list(t_data **mlx_)
{
	t_img_list	*current;
	t_img_list	*temp;
	t_data		*mlx;

	mlx = *mlx_;
	current = mlx->img_l;
	if (!(current->next))
		return ;
	while (current->next)
	{
		temp = current;
		current = current->next;
		current->back = temp;
	}
	mlx->img_tail = current;
}

void	raytracer_(t_obj_list *list, int argc)
{
	t_data	*mlx;

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

void            my_mlx_pixel_put(t_img_list *img_l, t_data *mlx, int x, int y, int color)
{
    char    *dst;

    dst = img_l->addr + (y * mlx->line_l + x * (mlx->bits_p_p / 8));
    *(unsigned int*)dst = color;
}
