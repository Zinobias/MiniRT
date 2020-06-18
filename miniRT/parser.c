/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 18:44:10 by zgargasc       #+#    #+#                */
/*   Updated: 2020/03/10 21:00:48 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj_list	**parser(void)
{
	int			ret;
	char		*line;
	int			fd;
	t_obj_list	**head;

	fd = open("scene.rt", O_RDONLY);
	ret = 3;
	make_head(&head);
	while (ret != 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == ERROR)
			error(GNL);
		if (line[0] != '\n')
			line_handler(line, &head);
	}
	close(fd);
	if (line)
		free(line);
	return (&head);
}
