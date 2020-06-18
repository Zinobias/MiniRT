/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 18:44:10 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/06/18 17:10:44 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj_list	*parser(void)
{
	int			ret;
	char		*line;
	int			fd;
	t_obj_list	*head;

	fd = open("scene.rt", O_RDONLY);
	ret = 3;
	make_head(&head);
	while (ret != 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == ERROR)
			error(GNL);
		if ((*line == '\n' || *line == '\0'))
		{
			if (line[1])
				error(INVAL);
		}
		else
			line_handler(line, &head);
	}
	close(fd);
	if (line)
		free(line);
	return (head);
}

int		main(void)
{
	t_obj_list *list;
	t_object	res;
	t_object	amb;
	t_object	cam;

	list = parser();
	res = list->object;
	list = list->next;
	amb = list->object;
	list = list->next;
	cam = list->object;
	printf("%f, %f, %f, %f, %f, %f, %f\n", cam.cam.view_p.x, cam.cam.view_p.y, cam.cam.view_p.z, cam.cam.norm_vec.x, cam.cam.norm_vec.y, cam.cam.norm_vec.z, cam.cam.fov);
	printf("%i / %i\n", res.res.x, res.res.y);
	printf("%i / %f\n", amb.amb.colors, amb.amb.ratio);
	exit(0);
	return (0);
}