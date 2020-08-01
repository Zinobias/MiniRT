/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 18:44:10 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/01 21:18:42 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj_list	*parser(int fd)
{
	int			ret;
	char		*line;
	t_obj_list	*head;

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
		if (line)
			free(line);
	}
	return (head);
}
