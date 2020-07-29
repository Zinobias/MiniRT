/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/08 19:58:36 by zgargasc       #+#    #+#                */
/*   Updated: 2019/12/08 20:19:28 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line_bonus.h"

size_t		ft_strlen(const char *s)
{
	size_t			i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\n')
		i++;
	return (i);
}

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	char			*s;
	const char		*c;

	if (!dst && !src)
		return (NULL);
	c = src;
	s = dst;
	i = 0;
	while (i < n)
	{
		s[i] = c[i];
		i++;
	}
	return ((void*)dst);
}

char		*copy_buff(char *old, char *buff, size_t i)
{
	char		*new;
	size_t		len;

	if (old == NULL)
	{
		new = (char*)malloc((i + 1) * sizeof(char));
		if (new == NULL)
			return (NULL);
		ft_memcpy(new, buff, i + 1);
	}
	else
	{
		len = ft_strlen(old);
		new = (char*)malloc((len + i + 1) * sizeof(char));
		if (new == NULL)
			return (NULL);
		ft_memcpy(new, old, len);
		free(old);
		ft_memcpy(new + len, buff, i + 1);
	}
	return (new);
}
