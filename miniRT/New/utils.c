/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 18:35:54 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/01 04:11:05 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3(double x, double y, double z)
{
	t_vec3	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vec2	vec2(int x, int y)
{
	t_vec2	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

void	check_vec3_range(t_vec3 data, double min, double max)
{
	if ((data.x > max || data.y > max || data.z > max)
	|| (data.x < min || data.y < min || data.z < min))
		error(INVAL);
}

void	check_line_valid(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			error(INVAL);
		i++;
	}
	return ;
}

void	make_head(t_obj_list **head)
{
	t_obj_list	*new_head;

	new_head = (t_obj_list *)malloc(sizeof(t_obj_list));
	if (!new_head)
		error(MALLOC);
	new_head->rac = 0;
	new_head->obj_type = NULL;
	new_head->next = NULL;
	*head = new_head;
	return ;
}

void	error(int code)
{
	if (code == INVAL)
		write(1, "ERROR\nINVALID SCENE", 20);
	if (code == MALLOC)
		write(1, "ERROR\nMALLOC", 13);
	if (code == GNL)
		write(1, "ERROR\nGET_NEXT_LINE", 20);
	if (code == MLX)
		write(1, "ERROR\nMLX", 10);
	if (code == INVAL_I)
		write(1, "ERROR\nBAD INPUT", 16);
	if (code == OPEN_CLOSE_WRITE)
		write(1, "ERROR\nOpen/close/Write, bad return val", 39);
	exit(1);
}

int	close_window_esc(int keycode, t_data *mlx)
{
	t_img_list	*temp;
	t_img_list	*current;

	current = mlx->img_l;
	if (keycode == 53)
	{
		while (current)
		{
			temp = current->img;
			mlx_destroy_image(mlx->mlx, temp);
			current = current->next;
		}
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return (0);
}

int		close_win_x(t_data *mlx)
{
	t_img_list	*temp;
	t_img_list	*current;

	current = mlx->img_l;
	while (current)
	{
		temp = current->img;
		mlx_destroy_image(mlx->mlx, temp);
		current = current->next;
	}
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
	return (0);
}

void	l_get_A(t_data **mlx_data, t_obj_list **list)
{
	t_obj_list	*current;

	current = *list;
	if (current->obj_type->f_code == AMB)
	{
		(*mlx_data)->ambient_light = current->object.amb;
		rm_element(list, AMB);
		return ;
	}
	else while (current->next)
	{
		if (current->obj_type->f_code == AMB)
			break;
		current = current->next;
	}
	(*mlx_data)->ambient_light = current->object.amb;
	rm_element(list, AMB);
	return ;
}

void	l_get_R(t_data **mlx_data, t_obj_list **list)
{
	t_obj_list	*current;

	current = *list;
	if (current->obj_type->f_code == RES)
	{
		(*mlx_data)->res = current->object.res;
		rm_element(list, RES);
		return ;
	}
	else while (current->next)
	{
		if (current->obj_type->f_code == RES)
			break;
		current = current->next;
	}
	(*mlx_data)->res = current->object.res;
	rm_element(list, RES);
	return ;
}

void	rm_element(t_obj_list **list, int obj_code)
{
	t_obj_list *current;
	t_obj_list *temp;

	current = *list;
	if (current->obj_type->f_code == obj_code)
	{
		if (current->next)
			*list = current->next;
		if (current)
			free(current);
	}
	else while (current->next)
	{
		if (current->next->obj_type->f_code == obj_code)
		{
			temp = current->next;
			current = current->next->next;
			break;
		}
		current = current->next;
	}
	return ;
}

void cam_head(t_data **mlx_data, t_cam vals)
{
	t_data *mlx;

	mlx = *mlx_data;
	mlx->img_l = (t_img_list*)malloc(sizeof(t_img_list));
	if (!mlx->img_l)
		error(MALLOC);
	mlx->img_l->cam = 1;
	mlx->img_l->next = NULL;
	mlx->img_l->back = NULL;
	mlx->img_l->addr = NULL;
	mlx->img_l->img = NULL;
	mlx->img_l->img = mlx_new_image(mlx->mlx, mlx->res.x, mlx->res.y);
	if (!mlx->img_l->img)
		error(MLX);
	mlx->img_l->addr =	mlx_get_data_addr(mlx->img_l->img, &mlx->bits_p_p, &mlx->line_l, &mlx->endian);
	if (!mlx->img_l->addr)
		error(MLX);
	mlx->img_l->cam_vals = vals;
	return ;
}

void create_cam_node(t_img_list **img_l, t_data **mlx_data, t_cam vals)
{
	int			temp;
	t_img_list	*current;
	t_data		*mlx;

	mlx = *mlx_data;
	current = *img_l;
	temp = current->cam;
	current->next = (t_img_list*)malloc(1 * sizeof(t_img_list));
	if (!current->next)
		error(MALLOC);
	current->next->cam = temp + 1;
	current->next->back = current;
	current->next->next = NULL;
	current->next->back = NULL;
	current->next->addr = NULL;
	current->next->img = NULL;
	current->next->img = mlx_new_image(mlx->mlx, mlx->res.x, mlx->res.y);
	if (!current->next->img)
		error(MLX);
	current->next->addr =	mlx_get_data_addr(current->next->img, &mlx->bits_p_p, &mlx->line_l, &mlx->endian);
	if (!current->next->addr)
		error(MLX);
	current->next->cam_vals = vals;
	return ;
}

void mlx_get_cams(t_data **mlx_data, t_obj_list **obj_l)
{
	t_data 		*mlx;
	t_obj_list 	*current;
	t_img_list	*current_i;
	
	mlx = *mlx_data;
	current = *obj_l;
	while (current)
	{
		if (current->obj_type->f_code == CAM)
		{
			if (!mlx->img_l)
			{
				cam_head(&mlx, current->object.cam);
				current_i = mlx->img_l;
			}
			else 
			{
				while (current_i->next)
					current_i = current_i->next;
				create_cam_node(&current_i, mlx_data, current->object.cam);
			}
			rm_element(obj_l, CAM);
		}
		current = current->next;
	}
}

void	mlx_hooks_(t_data **mlx_)
{
	t_data *mlx;

	mlx = *mlx_;
	mlx_key_hook(mlx->win, close_window_esc, mlx);
	mlx_hook(mlx->win, 17, 0, close_win_x, mlx);
	mlx_loop(mlx->mlx);
	return ;
}

t_vec3	vec3_x_matrix(t_vec3 *from, t_mat4 *c2w)
{
	t_vec3	new;

	new.x = from->x * c2w->x.x + from->y * c2w->y.x + from->z * c2w->z.x;
	new.y = from->x * c2w->x.y + from->y * c2w->y.y + from->z * c2w->z.y;
	new.z = from->x * c2w->x.z + from->y * c2w->y.z + from->z * c2w->z.z;
	return (new);
}

t_vec3	setcam(t_vec3 from, t_img_list *dest)
{
	t_vec3 new;
	t_mat4 c2w;

	if (dest->cam_vals.norm_vec.x == 0 && dest->cam_vals.norm_vec.y == 0 && dest->cam_vals.norm_vec.z == 0 )
		return(from);
	c2w = look_at(dest->cam_vals.view_p, vectorPlus(&dest->cam_vals.view_p, &dest->cam_vals.norm_vec));
	new = vec3_x_matrix(&from, &c2w);
	return (new);
}

t_mat4	look_at(t_vec3 from, t_vec3 to)
{
	t_mat4	new;
	t_vec3	temp;
	t_vec3	norm;

	norm = vectorSub(&to, &from);
	norm = vec_normalize(&norm);
	if (norm.x == 0.0 && norm.z == 0.0 && fabs(norm.y) == 1.0)
	{
		new.x = norm.y == 1.0 ? vec3(1.0,0.0,0.0) : vec3(0.0,0.0,1.0);
		new.y = norm.y == 1.0 ? vec3(0.0,0.0,1.0) : vec3(1.0,0.0,0.0);
		new.z = norm.y == 1.0 ? vec3(0.0,1.0,0.0) : vec3(0.0,-1.0,0.0);
		return(new);
	}
	temp = vec3(0.0,1.0,0.0);
	temp = vec_normalize(&temp);
	new.z = vectorSub(&from, &to);
	new.z = vec_normalize(&new.z);
	new.x = crossproduct(&temp, &new.z);
	new.y = crossproduct(&new.z, &new.x);
	new.l = vec3(0,0,0);
	return (new);
}

/*
** new.z = forward vector
** new.x = right
** new.y = uppguide
** new.l = translation vector
** if norm.x / z && y are at these specific cords, it is a
** achilles heel of the look-up function, thus it has to be hardcoded
** Because When the camera is vertical looking straight down or straight up, 
** the forward axis gets very close to the arbitrary axis used to compute the right axis.
** thus the crossproduct won't have a valid result.
*/

void	mlx_get_lights(t_data **mlx_, t_obj_list **list)
{
	t_obj_list	*current;
	t_data		*mlx;
	t_light_l	*current_l;

	current = *list;
	mlx = *mlx_;
	while(current)
	{
		if (current->obj_type->f_code == LIGHT)
		{
			if (!mlx->l_head)
			{
				create_light_head(&mlx, current->object.light);
				current_l = mlx->l_head;
			}
			else 
			{
				while (current_l->next)
					current_l = current_l->next;
				create_light_node(&current_l, current->object.light);
			}
			rm_element(list, LIGHT);
		}
		current = current->next;
	}
}


void	create_light_head(t_data **target, t_light object)
{
	t_data		*current;
	
	current = *target;
	current->l_head = (t_light_l*)malloc(sizeof(t_light_l));
	if (!current->l_head)
		error(MALLOC);
	current->l_head->t_light = object;
	current->l_head->next = NULL;
	return ;
}

void	create_light_node(t_light_l	**target, t_light object)
{
	t_light_l	*current;
	
	current = *target;
	current->next = (t_light_l*)malloc(sizeof(t_light_l));
	if (!current->next)
		error(MALLOC);
	current->next->t_light = object;
	current->next->next = NULL;
	return ;
}

t_colors get_pixel(t_data *mlx, int x, int y)
{
	unsigned		i;
	unsigned int	color;
	t_colors		col;

	i = y * mlx->line_l + x * (mlx->bits_p_p / 8);
	color = *(unsigned int*)(mlx->img_l->addr + i);
	col = get_c_struct(color);
	return (col);
}

// file header for bmp file;
// 0x4d42 is the file type BM
// type -- size -- offset  -- non reserved
static void create_bmp_file_header(char *buf, size_t fsize)
{
	*((uint16_t *)&buf[0x00]) = (uint16_t)0x4d42; // 0x00 BMP signature 'B' 'M'
	*((uint32_t *)&buf[0x02]) = (uint32_t)fsize; // 0X02 size in bytes of the file, including heder and pixel data;
	// 0x06 unused, reserved data
	
	*((uint32_t *)&buf[0x0A]) = (uint32_t)0X0E + 40; // data offset 0x0A
}	

// bmp info header
// https://elcharolin.wordpress.com/2018/11/28/read-and-write-bmp-files-in-c-c/
static void create_bmp_info_header(char *buf, t_data *mlx)
{
	*((uint32_t *)&buf[0x0E]) = (uint32_t)40; // Size of header, fixed size 40 bytes
	*((uint32_t *)&buf[0x12]) = (uint32_t)mlx->res.x; // width img pix
	*((uint32_t *)&buf[0x16]) = (uint32_t)mlx->res.y; // height img pix
	*((uint16_t *)&buf[0x1A]) = (uint16_t)1; // numb color planes, must be 1
	*((uint16_t *)&buf[0x1C]) = (uint16_t)24; // number of bits pp
}	
//  3 * x & y. 3 is the amount of bytes pp, x * y is the amount of bytes
// 14 = fileheadersize
// 40 = infoheadersize
// fsize

// get ft_bzero from my libft
static void fill_bmp(char *buf, t_data *mlx)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	i;
	t_colors	col;

	y = (unsigned int)mlx->res.y - 1;
	i = 0x0E + 40;
	while (y > 0)
	{
		x = 0;
		while (x < mlx->res.x)
		{
			col = get_pixel(mlx, x, y);
			buf[i + 0] = (unsigned int)col.b;
			buf[i + 1] = (unsigned int)col.g;
			buf[i + 2] = (unsigned int)col.r;
			i += 3;
			x++;
		}
		y--;
	}
}

void	save_img(t_data *mlx)
{
	int		fd;
	size_t	fsize;
	char	*buf;

	fd = open("ScreenyUwU.bmp", O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		error(OPEN_CLOSE_WRITE);
	fsize = 57 * (unsigned int)((int)mlx->res.x * (int)mlx->res.y);
	buf = calloc(fsize, 1);
	// use ft_calloc instead
	if (!buf)
		error(MALLOC);
	create_bmp_file_header(buf, fsize);
	create_bmp_info_header(buf, mlx);
	fill_bmp(buf, mlx);
	if (write(fd, buf, fsize) < 0)
		error(OPEN_CLOSE_WRITE);
	if (close(fd) == -1)
		error(OPEN_CLOSE_WRITE);
	free(buf);
}