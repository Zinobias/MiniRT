/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reader_basic.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/11 07:02:56 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/13 14:28:32 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

char			*rd_rgb(char *s, t_rgb *rgb)
{
	rgb->packed.r = (unsigned char)ft_atoi(s);
	while (*s != ',')
		s++;
	s++;
	rgb->packed.g = (unsigned char)ft_atoi(s);
	while (*s != ',')
		s++;
	s++;
	rgb->packed.b = (unsigned char)ft_atoi(s);
	while (ft_isdigit(*s) || *s == '.' || *s == '-')
		s++;
	rgb->packed.a = 0;
	return (s);
}

char			*rd_vect(char *s, t_vect *vect)
{
	vect->x = ft_atof(s);
	while (*s != ',')
		s++;
	s++;
	vect->y = ft_atof(s);
	while (*s != ',')
		s++;
	s++;
	vect->z = ft_atof(s);
	while (ft_isdigit(*s) || *s == '.' || *s == '-')
		s++;
	return (s);
}

void			rd_res(char *s, t_base *b)
{
	s++;
	while (*s == ' ' || *s == '\t')
		s++;
	b->res.x_max = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	s++;
	b->res.y_max = ft_atoi(s);
}

void			rd_amb(char *s, t_base *b)
{
	s++;
	while (*s == ' ' || *s == '\t')
		s++;
	b->amb.amb = ft_atof(s);
	while (ft_isdigit(*s) || *s == '.' || *s == '-')
		s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_rgb(s, &b->amb.rgb);
}

void			rd_cam(char *s, t_base *b)
{
	s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_vect(s, &b->cam.c[b->i_c].pos);
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_vect(s, &b->cam.c[b->i_c].vec);
	while (*s == ' ' || *s == '\t')
		s++;
	b->cam.c[b->i_c].fov = ft_atoi(s);
}

void			rd_light(char *s, t_base *b)
{
	s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_vect(s, &b->light[b->i_l].pos);
	while (*s == ' ' || *s == '\t')
		s++;
	b->light[b->i_l].bright = ft_atof(s);
	while (ft_isdigit(*s) || *s == '.' || *s == '-')
		s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_rgb(s, &b->light[b->i_l].rgb);
}
