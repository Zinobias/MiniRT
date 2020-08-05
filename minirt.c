/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 21:29:41 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/05 17:48:11 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	check_string(char *s)
{
	int					i;
	static const char	*example = "--save";

	i = 0;
	while (i < 7)
	{
		if (s[i] != example[i])
			error("Invalid command line input", 27);
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_obj_list		*list;
	int				fd;

	if (argc != 2 && argc != 3)
		error("Invalid command line input", 27);
	if (argc == 3)
		check_string(argv[2]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error("Opening f_name.rt went wrong", 29);
	list = parser(fd);
	if (close(fd) == -1)
		error("Closing f_name.rt fd went wrong", 32);
	raytracer_(list, argc);
	exit(0);
	return (0);
}
