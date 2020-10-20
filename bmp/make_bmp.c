/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_bmp.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/01 17:54:47 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/10/20 15:10:09 by zilisabethp   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**file header for bmp file;
** 0x4d42 is the file type BM
** type -- size -- offset  -- non reserved
** 0X02 size in bytes of the file, including heder and pixel data;
** 0x00 BMP signature 'B' 'M'
** 0x06 unused, reserved data
** data offset 0x0A
*/

static void	create_bmp_file_header(char *buf, size_t fsize)
{
	*((uint16_t *)&buf[0x00]) = (uint16_t)0x4d42;
	*((uint32_t *)&buf[0x02]) = (uint32_t)fsize;
	*((uint32_t *)&buf[0x0A]) = (uint32_t)54;
}

/*
** bmp info header
** https://elcharolin.wordpress.com/2018/11/28/read-and-write-bmp-files-in-c-c/
** Size of header, fixed size 40 bytes
** width img pix
** height img pix
** numb color planes, must be 1
** number of bits pp
*/

static void	create_bmp_info_header(char *buf, t_data *mlx)
{
	*((uint32_t *)&buf[0x0E]) = (uint32_t)40;
	*((uint32_t *)&buf[0x12]) = (uint32_t)mlx->res.x;
	*((uint32_t *)&buf[0x16]) = (uint32_t)mlx->res.y;
	*((uint16_t *)&buf[0x1A]) = (uint16_t)1;
	*((uint16_t *)&buf[0x1C]) = (uint16_t)24;
}

/*
** 3 * x & y. 3 is the amount of bytes pp, x * y is the amount of bytes
** 14 = fileheadersize
** 40 = infoheadersize
** fsize
** if (i % 4) is for padding, when res is 1023 for example
*/

static void	fill_bmp(char *buf, t_data *mlx)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	i;
	t_colors	col;

	y = (unsigned int)mlx->res.y - 1;
	i = 0x0E + 40;
	while (y > 0)
	{
		x = 0;
		while (x < mlx->res.x)
		{
			col = get_pixel(mlx, x, y);
			buf[i + 0] = (uint8_t)col.b;
			buf[i + 1] = (uint8_t)col.g;
			buf[i + 2] = (uint8_t)col.r;
			i += 3;
			x++;
		}
		if ((i - 0x0E + 40) % 4)
			i += (i % 4);
		y--;
	}
}

void		save_img(t_data *mlx)
{
	int			fd;
	size_t		fsize;
	char		*buf;

	fd = open("ScreenyUwU.bmp", O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		error("save img open went wrong", 25);
	fsize = 54 + (unsigned int)((((int)mlx->res.x * 3) +
		((int)mlx->res.x % 4)) * (int)mlx->res.y);
	buf = ft_calloc(fsize, 1);
	if (!buf)
		error("save img, buf malloc went wrong", 32);
	create_bmp_file_header(buf, fsize);
	create_bmp_info_header(buf, mlx);
	fill_bmp(buf, mlx);
	if (write(fd, buf, fsize) < 0)
		error("save img, write went wrong", 27);
	if (close(fd) == -1)
		error("save img, close went wrong", 27);
	free(buf);
	clear_img_l(mlx);
	exit(0);
}
