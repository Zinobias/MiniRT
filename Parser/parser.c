/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 18:44:10 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/10/20 14:47:00 by zilisabethp   ########   odam.nl         */
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
			if (*line)
				error("Invalid line", 13);
		}
		else
			line_handler(line, &head);
		if (line)
			free(line);
	}
	if (!(head->rac & 1 && head->rac & 2))
		error("Missing R || A", 15);
	return (head);
}
