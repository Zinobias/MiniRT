/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 14:49:45 by zgargasc      #+#    #+#                 */
/*   Updated: 2020/08/05 17:57:46 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	str = b;
	i = 0;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return ((void *)b);
}

void			*ft_calloc(size_t count, size_t size)
{
	void		*new;

	new = malloc(count * size);
	if (new == NULL)
		return (NULL);
	ft_memset(new, '\0', size * count);
	return (new);
}
