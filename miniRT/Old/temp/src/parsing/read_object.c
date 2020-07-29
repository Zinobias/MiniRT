/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_object.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/11 06:26:05 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/13 14:28:38 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

void			rd_sphere(char *s, t_objs *o)
{
	o->type = 's';
	s++;
	s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_vect(s, &o->pos1);
	while (*s == ' ' || *s == '\t')
		s++;
	o->dia = ft_atof(s);
	while (ft_isdigit(*s) || *s == '.' || *s == '-')
		s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_rgb(s, &o->rgb);
}

void			rd_plane(char *s, t_objs *o)
{
	o->type = 'p';
	s++;
	s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_vect(s, &o->pos1);
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_vect(s, &o->vec);
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_rgb(s, &o->rgb);
}

void			rd_square(char *s, t_objs *o)
{
	o->type = 'q';
	s++;
	s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_vect(s, &o->pos1);
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_vect(s, &o->vec);
	while (*s == ' ' || *s == '\t')
		s++;
	o->size = ft_atof(s);
	while (ft_isdigit(*s) || *s == '.' || *s == '-')
		s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_rgb(s, &o->rgb);
}

void			rd_cylinder(char *s, t_objs *o)
{
	o->type = 'c';
	s++;
	s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_vect(s, &o->pos1);
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_vect(s, &o->vec);
	while (*s == ' ' || *s == '\t')
		s++;
	o->dia = ft_atof(s);
	while (ft_isdigit(*s) || *s == '.' || *s == '-')
		s++;
	while (*s == ' ' || *s == '\t')
		s++;
	o->height = ft_atof(s);
	while (ft_isdigit(*s) || *s == '.' || *s == '-')
		s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_rgb(s, &o->rgb);
}

void			rd_triangle(char *s, t_objs *o)
{
	o->type = 't';
	s++;
	s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_vect(s, &o->pos1);
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_vect(s, &o->pos2);
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_vect(s, &o->pos3);
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_rgb(s, &o->rgb);
}
