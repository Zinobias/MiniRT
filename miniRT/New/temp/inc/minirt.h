/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/30 10:28:36 by ldideric      #+#    #+#                 */
/*   Updated: 2020/06/25 15:17:12 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <libft.h>
# include <ft_printf.h>

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

//pl  0,0,0            0,1.0,0                                  255,0,255
//sq  0.0,0.0,20.6     1.0,0.0,0.0      12.6                    255,0,255
//cy  50.0,0.0,20.6    0,0,1.0          14.2        21.42       10,0,255
//tr  10,20,10         10,10,20         20,10,10                0,0,255

/*
** DEFINES ---------------------------------------------------- |
*/

# define WIN_NAME "bepis is better than pepsi"
# define TRUE	1
# define FALSE	0

/*
** ERROR MESSAGES
*/

# define ERR_IN_RT_FILE		0
# define ERR_MALLOC			1
# define ERR_MLX			2
# define ERR_NO_RT			3

/*
** STRUCTS ---------------------------------------------------- |
*/

typedef struct		s_col
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}					t_col;

typedef union		u_rgb
{
	unsigned int	color;
	t_col			packed;
}					t_rgb;

typedef struct		s_res
{
	int				x_max;
	int				y_max;
}					t_res;

typedef struct		s_vect
{
	double			x;
	double			y;
	double			z;
	int				hit;
}					t_vect;

typedef struct		s_light
{
	t_vect			pos;
	t_rgb			rgb;
	double			bright;
}					t_light;

typedef struct		s_cam
{
	t_vect			pos;
	t_vect			vec;
	int				fov;
}					t_cam;

typedef struct		s_cams
{
	t_cam			*c;
	int				max;
}					t_cams;

typedef struct		s_amb
{
	double			amb;
	t_rgb			rgb;
}					t_amb;

/*
** all basic input from mini.rt file
*/
typedef struct		s_base
{
	t_res			res;
	t_amb			amb;
	t_cams			cam;
	t_light			*light;
	char			*file;
	int				i_c;
	int				i_l;
}					t_base;

/*
** A struct for any kind of object.
*/
typedef struct		s_objs
{
	char			type;
	t_vect			hit;
	t_vect			pos1;
	t_vect			pos2;
	t_vect			pos3;
	t_vect			vec;
	int				normal;
	double			dia;
	double			height;
	double			size;
	t_rgb			rgb;
}					t_objs;

/*
** | ----------------------------------------------------------------------- |
*/

typedef struct		s_data
{
	void			*img;
	char			*addr;
	int				bpp;
	int				len;
	int				endian;
	t_base			b;
	t_objs			*o;
	void			**sav;
}					t_data;

typedef struct		s_vars
{
	void			*mlx;
	void			*win;
	t_data			data;
}					t_vars;

/*
** | ----------------------------------------------------------------------- |
*/

typedef void		(*t_read_b)(char *s, t_base *b);
typedef void		(*t_read_o)(char *s, t_objs *o);
typedef t_vect		(*t_hit_o)(t_vect *rd, t_data *data, t_objs *o);

void				printer(t_objs *o);
void				graphing(t_data *img, int x_max, int y_max);

void				my_mlx_pixel_put(t_data *data, int x, int y, int color);

void				*px_loop(t_data *data);
unsigned int		each_px(t_vect *rd, t_data *data);
unsigned int		first_hit(t_data *data);
t_vect				hit_checker(t_vect *rd, t_objs *o, t_data *data);

void				*errors(int error);
void				hooks(t_vars *vars);

/*
** Object functions
*/

t_vect				sphere(t_vect *rd, t_data *data, t_objs *o);
t_vect				plane(t_vect *rd, t_data *data, t_objs *o);
t_vect				triangle(t_vect *rd, t_data *data, t_objs *o);

/*
** Math functions
*/

t_vect				ft_normalize(t_vect p);

double				get_ndcy_pos(t_base *b, int y);
double				get_ndcx_pos(t_base *b, int x);

t_vect				vect_min(t_vect a, t_vect b);
t_vect				vect_plus(t_vect a, t_vect b);

t_vect				cross_pr(t_vect a, t_vect b);
double				dot(t_vect v, t_vect u);
double				length(t_vect v);
double				length_betw(t_vect a, t_vect b);
t_vect				vec3(double x, double y, double z);

/*
** Reader functions
*/

void				*read_starter(t_data *d);
t_objs				*read_loop(t_base *b, t_objs *o, char *s);
int					obj_cntr(char *s);
int					cam_light_cntr(char *s, char c);
void				*reader_free(void *a, void *b, void *c, void *d);

char				*rd_vect(char *s, t_vect *vect);
char				*rd_rgb(char *s, t_rgb *rgb);

void				rd_res(char *s, t_base *t);
void				rd_amb(char *s, t_base *t);
void				rd_cam(char *s, t_base *t);
void				rd_light(char *s, t_base *t);

void				rd_sphere(char *s, t_objs *o);
void				rd_plane(char *s, t_objs *o);
void				rd_square(char *s, t_objs *o);
void				rd_cylinder(char *s, t_objs *o);
void				rd_triangle(char *s, t_objs *o);

#endif
