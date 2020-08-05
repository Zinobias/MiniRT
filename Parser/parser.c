/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 18:44:10 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/05 17:48:24 by zgargasc      ########   odam.nl         */
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
			error("GNL went wrong", 15);
		if ((*line == '\n' || *line == '\0'))
		{
			if (line[1])
				error("Invalid line", 13);
		}
		else
			line_handler(line, &head);
		if (line)
			free(line);
	}
	return (head);
}
