/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 16:17:19 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/06/20 17:32:44 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <fcntl.h>
#include <mlx.h>

typedef	enum	e_error {
ERROR = -1,
INVAL = 1,
MALLOC = 2,
GNL = 3,
MLX = 4,
}				t_error;

typedef	enum	e_f_code {
RES = 0,
AMB = 1,
CAM = 2,
LIGHT = 3,
SPH = 4,
PL = 5,
SQ = 6,
CY = 7,
TR = 8,
}				t_f_code;

typedef struct  s_vec2 {
	double		x;
	double		y;
}               t_vec2;

typedef struct  s_vec3 {
	double		x;
	double		y;
	double		z;
}               t_vec3;

typedef struct  s_atod_ret {
	double		val;
	int			i;
}               t_atod_ret;

typedef struct  s_d_ret {
	double		val;
	int			i;
}               t_d_ret;

typedef struct  s_f3_ret {
	int			fields;
	int			i;
	t_vec3		f_info;
}               t_f3_ret;

typedef struct  s_i_ret {
	int			val;
	int			i;
}               t_i_ret;

typedef struct	s_res {
	int			x;
	int			y;
}				t_res;

typedef struct	s_amb {
	double		ratio;
	int			colors;
}				t_amb;

typedef struct	s_cam {
	t_vec3		view_p;
	t_vec3		norm_vec;
	double		fov;
}				t_cam;

typedef struct	s_light {
	t_vec3		light_p;
	double		brightness;
	int			colors;
}				t_light;

typedef struct	s_pl {
	t_vec3		cords;
	t_vec3		norm_vec;
	int			colors;
}				t_pl;

typedef struct	s_sq {
	t_vec3		cords;
	t_vec3		norm_vec;
	double		side_size;
	int			colors;
}				t_sq;

typedef struct	s_cy {
	t_vec3		cords;
	t_vec3		norm_vec;
	double		dia;
	double		height;
	int			colors;
}				t_cy;

typedef struct	s_tr {
	t_vec3		point1;
	t_vec3		point2;
	t_vec3		point3;
	int			colors;
}				t_tr;

typedef struct	s_sph {
	t_vec3		center;
	int			diam;
	int			colors;
}				t_sph;

typedef	union	u_object
{
	t_res		res;
	t_amb		amb;
	t_cam		cam;
	t_light		light;
	t_sph		sphere;
	t_pl		plane;
	t_sq		square;
	t_cy		cylinder;
	t_tr		triangle;
}				t_object;

typedef   t_object (*DataFunction)(char *str);

typedef struct  s_f_data {
	int			f_code;
	char		*str;
	DataFunction function;
}               t_f_data;

typedef struct  s_obj_list {
    t_f_data			*obj_type;
	t_object			object;
	unsigned short		rac;
	void 				*next;
}               t_obj_list;

// rename data to something more specific
typedef struct  s_data {
	void		*mlx;
	void		*win;
	t_res		res;
	int			ambient_light;
    void        *img;
    char        *addr;
    int         bits_p_p;
    int         line_l;
    int         endian;
}               t_data;

int					get_next_line(int fd, char **line);
void				obj_add(t_f_data *ojb_data, t_obj_list **list, char *line);
void				error(int);
t_vec3				vec3(int x, int y, int z);
t_vec2				vec2(int x, int y);
int					rgba(int r, int g, int b, int t);
int					get_t(int trgb);
int					get_r(int trgb);
int					get_g(int trgb);
int					get_b(int trgb);
t_d_ret				get_double(char *line);
t_i_ret				get_int(char *line);
t_f3_ret			get_fields(char *line);
t_atod_ret			ft_atod(char *str);
void				line_handler(char *line, t_obj_list **obj);
void           		my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_f_data			*line_to_data(char *line);
void				make_head(t_obj_list **head);
t_object			get_res(char *line);
t_object			get_amb(char *line);
t_object			get_cam(char *line);
t_object			get_light(char *line);
t_object			get_plane(char *line);
t_object			get_sphere(char *line);
t_object			get_square(char *line);
t_object			get_cylinder(char *line);
t_object			get_triangle(char *line);
void				check_line_valid(char *line);
void				check_vec3_range(t_vec3 data, double min, double max);
int					rgba(int t, int r, int g, int b);
t_obj_list			*parser(void);
int					close_window_esc(int keycode, t_data *mlx);
int				close_win_x(t_data *mlx);
#endif