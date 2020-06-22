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
	t_object	res;
	t_object	amb;
	t_object	cam;

	
	list = parser();
	if (list->rac & 1)
		printf("test 1\n");
	if (list->rac & 2)
		printf("test 2\n");
	if (list->rac & 4)
		printf("test 4\n");
	if (!(list->rac & 1) || !(list->rac & 2) || !(list->rac & 4))
		error(INVAL);
	res = list->object;
	list = list->next;
	amb = list->object;
	list = list->next;
	cam = list->object;
	printf("%f, %f, %f, %f, %f, %f, %f\n", cam.cam.view_p.x, cam.cam.view_p.y, cam.cam.view_p.z, cam.cam.norm_vec.x, cam.cam.norm_vec.y, cam.cam.norm_vec.z, cam.cam.fov);
	printf("%i / %i\n", res.res.x, res.res.y);
	printf("%i / %f\n", amb.amb.colors, amb.amb.ratio);
	rendering();
	exit(0);
	return (0);
}

void	rendering(void)
{
	t_data	mlx;

	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		error(MLX);
	mlx.img = mlx_new_image(mlx.mlx, 1920, 1080);
	if (!mlx.mlx || !mlx.img)
		error(MLX);
	mlx.win = mlx_new_window(mlx.mlx, 1920, 1080, "hello worlddd");
	if (!mlx.mlx || !mlx.win)
		error(MLX);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_p_p, &mlx.line_l, &mlx.endian);

	for (int i = 50; i < 200; i++) {
		for (int j = 50; j < 200; j++) {
			my_mlx_pixel_put(&mlx, i, j, rgba(0, 55, 55, 255));
		}
	}
	mlx_put_image_to_window(&mlx, mlx.win, mlx.img, 0, 0);
	mlx_key_hook(mlx.win, close_window_esc, &mlx);
	mlx_hook(mlx.win, 17, 0, close_win_x, &mlx);
	mlx_loop(mlx.mlx);
	return ;
}

void            my_mlx_pixel_put(t_data *mlx, int x, int y, int color)
{
    char    *dst;

    dst = mlx->addr + (y * mlx->line_l + x * (mlx->bits_p_p / 8));
    *(unsigned int*)dst = color;
}
