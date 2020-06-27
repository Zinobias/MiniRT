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
	// t_obj_list *list;
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
	rendering(parser());
	exit(0);
	return (0);
}

void	mlx_start(t_data **mlx_data, t_obj_list **list)
{
	t_data *mlx;

	mlx = (t_data*)malloc(sizeof(t_data));
	if (!mlx)
		error(MALLOC);
	*mlx_data = mlx;
	mlx->head = &mlx->img_l;
	mlx->res = l_get_R(list);
	mlx->ambient_light = l_get_A(list);
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		error(MLX);
	mlx->win = mlx_new_window(mlx->mlx, mlx->res.x, mlx->res.y, "hello worlddd");
	if (!mlx->win)
		error(MLX);
	return ;
}

	// for (int i = 50; i < 200; i++) {
	// 	for (int j = 50; j < 200; j++) {
	// 		my_mlx_pixel_put(mlx->img_l, mlx, i, j, rgba(0, 55, 55, 255));
	// 	}
	// }
void cam_head(t_data **mlx_data)
{
	t_data *mlx;

	mlx = *mlx_data;
	mlx->img_l = (t_img_list*)malloc(sizeof(t_img_list));
	if (!mlx->img_l)
		error(MALLOC);
	mlx->img_l->cam = 1;
	mlx->img_l->next = NULL;
	return ;
}

void create_cam_node(t_img_list **img_l)
{
	int			temp;
	t_img_list *current;

	current = *img_l;
	temp = current->cam;
	current->next = (t_img_list*)malloc(sizeof(t_img_list));
	if (!current->next)
		error(MALLOC);
	current->next->cam = temp + 1;
	current->next->next = NULL;
	return ;
}

void mlx_get_cams(t_data **mlx_data, t_obj_list **obj_l)
{
	t_data *mlx;
	t_obj_list *current;
	
	mlx = *mlx_data;
	current = *obj_l;
	while (current)
	{
		if (current->obj_type->f_code == CAM)
		{
			if (!*mlx->head)
				cam_head(&mlx);
			else while (mlx->img_l->next)
			{
				mlx->img_l = mlx->img_l->next;
				create_cam_node(mlx->img_l);
			}
			rm_element(obj_l, CAM);
		}
		current = current->next;
	}
	return ;
}

mlx_load_cams(&mlx, &list)
{

}
void	rendering(t_obj_list *list)
{
	t_data	*mlx;

	mlx_start(&mlx, &list);
	mlx_get_cams(&mlx, &list);
	mlx_load_cams(&mlx, &list);
	// mlx->img_l = (t_img_list*)malloc(sizeof(t_img_list));
	// if (!mlx->img_l)
	// 	error(MALLOC);
	// mlx->head = &mlx->img_l;

	mlx->img_l->img = mlx_new_image(mlx->mlx, mlx->res.x, mlx->res.y);
	if (!mlx->img_l->img)
		error(MLX);
	mlx->img_l->addr = mlx_get_data_addr(mlx->img_l->img, &mlx->bits_p_p, &mlx->line_l, &mlx->endian);

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img_l->img, 0, 0);
	mlx_key_hook(mlx->win, close_window_esc, mlx);
	mlx_hook(mlx->win, 17, 0, close_win_x, mlx);
	mlx_loop(mlx->mlx);
	return ;
}

void            my_mlx_pixel_put(t_img_list *img_l, t_data *mlx, int x, int y, int color)
{
    char    *dst;

    dst = img_l->addr + (y * mlx->line_l + x * (mlx->bits_p_p / 8));
    *(unsigned int*)dst = color;
}

