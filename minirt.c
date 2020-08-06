/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 21:29:41 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/06 16:58:25 by pani_zino     ########   odam.nl         */
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

static void	check_file_ext(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	if (s[i - 1] != 't' || s[i - 2] != 'r' || s[i - 3] != '.')
		error("Invald file extension", 22);
	return ;
}

int			main(int argc, char **argv)
{
	t_obj_list		*list;
	int				fd;

	if (argc != 2 && argc != 3)
		error("Invalid command line input", 27);
	if (argc == 3)
		check_string(argv[2]);
	if (argv[1])
		check_file_ext(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error("Opening file went wrong", 24);
	list = parser(fd);
	if (close(fd) == -1)
		error("Closing file fd went wrong", 27);
	raytracer_(list, argc);
	exit(0);
	return (0);
}
