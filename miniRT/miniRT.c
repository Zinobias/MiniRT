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

int		main(void)
{
	t_obj_list *list;
	// t_object	res;
	// t_object	amb;
	// t_object	cam;

	

	// if (list->rac & 1)
	// 	printf("test 1\n");
	// if (list->rac & 2)
	// 	printf("test 2\n");
	// if (list->rac & 4)
	// 	printf("test 4\n");
	// if (!(list->rac & 1) || !(list->rac & 2) || !(list->rac & 4))
	// 	error(INVAL);
	// res = list->object;
	// list = list->next;
	// amb = list->object;
	// list = list->next;
	// cam = list->object;
	// printf("%f, %f, %f, %f, %f, %f, %f\n", cam.cam.view_p.x, cam.cam.view_p.y, cam.cam.view_p.z, cam.cam.norm_vec.x, cam.cam.norm_vec.y, cam.cam.norm_vec.z, cam.cam.fov);
	// printf("%i / %i\n", res.res.x, res.res.y);
	// printf("%i / %f\n", amb.amb.colors, amb.amb.ratio);

	list = parser();
	raytracer_(list);
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
	mlx->res = l_get_R(list);
	mlx->ambient_light = l_get_A(list);
	mlx->mlx = mlx_init();
	mlx->img_l = NULL;
	if (!mlx->mlx)
		error(MLX);
	mlx->win = mlx_new_window(mlx->mlx, mlx->res.x, mlx->res.y, "Headache_generator_9000");
	if (!mlx->win)
		error(MLX);
	return ;
}

	// for (int i = 50; i < 200; i++) {
	// 	for (int j = 50; j < 200; j++) {
	// 		my_mlx_pixel_put(mlx->img_l, mlx, i, j, rgba(0, 55, 55, 255));
	// 	}
	// }
// const Vec3f &rayorig, const Vec3f &raydir, float &t0, float &t1

// t_ray	intersect_sph(const t_vec3 r_orig, const t_vec3 r_dir, t_obj_list *sphere, float t0, float t1)
// {
// 	t_ray ray;

// 	float tca = vectorDot(&r_dir, &r_dir); 
// 	t_vec3 dist = vectorMin(&sphere->object.sphere.center, &r_orig);
// 	tca = vectorDot(&dist, &r_dir);
// 	if (tca < 0) 
// 	{
// 		ray.colors = 0;
// 		return (ray);
// 	}
// 	float d2 = vectordot() - tca * tca; 
// 	if (d2 > (sphere->object.sphere.diam / 2)) 
// 	{
// 		ray.colors = 0;
// 		return (ray);
// 	} 
// 	float thc = sqrt((sphere->object.sphere.diam / 2) - d2); 
// 	t0 = tca - thc; 
// 	t1 = tca + thc; 
// 	ray.colors = sphere->object.sphere.colors;
// 	return (ray);
// }

// int	trace(const t_vec3 r_orig, const t_vec3 r_dir, t_obj_list **head)
// {
// 	t_obj_list	*current;
// 	t_ray		ray;
// 	t_ray		temp;
// 	// float		t0;
// 	// float		t1;

// 	// t0 = 0;
// 	// t1 = 0;
// 	current = *head;
// 	ray.norm_dir = 0;
// 	temp.norm_dir = 0;
// 	while (current)
// 	{
// 		temp = intersect_sph(r_orig, r_dir, current, t0, t1);
// 		ray.norm_dir = ray.norm_dir < temp.norm_dir ? ray.norm_dir : temp.norm_dir;
// 		ray.colors = ray.norm_dir < temp.norm_dir ? temp.colors : temp.colors;
// 		current = current->next;
// 	}
// 	return (ray.colors);
// }

void	render_(t_data **mlx_, t_obj_list **head, t_img_list *dest)
{
	t_data 	*mlx;
	t_ray	*ray;
	
	int		y;
	int		x;

	ray = (t_ray*)malloc(1 * sizeof(t_ray));
	if (!ray)
		error(MALLOC);
	y = 0;
	mlx = *mlx_;
	mlx->aspect_ratio = mlx->res.x / mlx->res.y;
	ray->angle = tan(M_PI * 0.5 * dest->cam_vals.fov / 180.);
	// ray->angle = tan(dest->cam_vals.fov / 2 * M_PI / 180);
	// float xx;
	// float yy;

	// xx = 0;
	// yy = 0;
	ray->orig = dest->cam_vals.view_p;
	while (y < mlx->res.y)
	{
		x = 0;
		while (x < mlx->res.x)
		{
			// xx = ((2 * ((x + 0.5) / (mlx->res.x)) - 1) * ray->angle * mlx->aspect_ratio) - dest->cam_vals.view_p.x;
            // yy = ((1 - 2 * ((y + 0.5) / (mlx->res.x))) * ray->angle) - dest->cam_vals.view_p.y;
			ray->dir = vec3(((2 * ((x + 0.5) / (mlx->res.x)) - 1) * ray->angle * mlx->aspect_ratio) - dest->cam_vals.view_p.x,
			 ((1 - 2 * ((y + 0.5) / (mlx->res.x))) * ray->angle) - dest->cam_vals.view_p.y , -1 - dest->cam_vals.view_p.z);
			// printf("x : [%lf] -- y : [%lf] -- z : [%lf]\n)", ray->dir.x, ray->dir.y, ray->dir.z);
			ray->norm_dir = vec_normalize(&ray->dir, sqrt(vectorDot(&ray->dir, &ray->dir)));
			printf("x : [%f] -- y : [%f] -- z : [%f]\n)", ray->norm_dir.x, ray->norm_dir.y, ray->norm_dir.z);
			x++;
			(void)head;
		}
		y++;
	}
	// )x : [-0.920259] -- y : [-0.006884] -- z : [-0.391250]
	printf("aspect ratio : [%lf] -- angle : [%lf]\n", mlx->aspect_ratio, ray->angle);
	printf("%i\n", x);
	printf("%i\n", y);
	if (ray)
		free(ray);
	return ;
}

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
		(void)head;
		current = current->next;
	}
	return ;
}

void	raytracer_(t_obj_list *list)
{
	t_data	*mlx;

	mlx_start(&mlx, &list);
	mlx_get_cams(&mlx, &list);
	printf("Cam : [%i]\n", mlx->img_l->cam);
	// printf("Cam : [%i]\n", mlx->img_l->next->cam);
	mlx_load_cams(&mlx, &list);
	mlx_hooks_(&mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img_l->img, 0, 0);
	return ;
}

void            my_mlx_pixel_put(t_img_list *img_l, t_data *mlx, int x, int y, int color)
{
    char    *dst;

    dst = img_l->addr + (y * mlx->line_l + x * (mlx->bits_p_p / 8));
    *(unsigned int*)dst = color;
}

// mlx->img_l = (t_img_list*)malloc(sizeof(t_img_list));
	// if (!mlx->img_l)
	// 	error(MALLOC);
	// mlx->head = &mlx->img_l;

	// mlx->img_l->img = mlx_new_image(mlx->mlx, mlx->res.x, mlx->res.y);
	// if (!mlx->img_l->img)
	// 	error(MLX);
	// mlx->img_l->addr = mlx_get_data_addr(mlx->img_l->img, &mlx->bits_p_p, &mlx->line_l, &mlx->endian);

