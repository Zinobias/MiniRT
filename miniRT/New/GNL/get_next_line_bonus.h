/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/08 19:59:00 by zgargasc       #+#    #+#                */
/*   Updated: 2019/12/08 20:19:25 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
# include <stdlib.h>
# include <unistd.h>

typedef enum	e_ret_val
{
	ERROR = -1,
	EOF_ = 0,
	LINE_READ = 1,
	LOOP = 2
}				t_ret_val;

typedef	struct	s_list
{
	int				fd;
	char			*buff;
	size_t			char_c;
	struct s_list	*next;
}				t_list;

char			*copy_buff(char *old, char *buff, size_t i);
size_t			ft_strlen(const char *s);
void			*ft_memcpy(void *dst, const void *src, size_t n);
int				get_next_line(int fd, char **line);
t_list			*ft_lstnew(int	fd);

#endif
