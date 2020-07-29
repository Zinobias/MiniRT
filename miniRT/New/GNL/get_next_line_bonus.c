/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/08 19:57:47 by zgargasc       #+#    #+#                */
/*   Updated: 2019/12/12 13:49:22 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void		free_buff(t_list **head, int fd)
{
	t_list	*current;
	t_list	*temp;

	current = *head;
	if (current->fd == fd)
	{
		*head = current->next;
		free(current->buff);
		free(current);
	}
	else
		while (current)
		{
			if (current->next->fd == fd)
			{
				temp = current->next;
				current->next = current->next->next;
				free(temp->buff);
				free(temp);
			}
			current = current->next;
		}
}

t_list		*ft_lstnew(int fd)
{
	t_list				*new_elem;

	new_elem = (t_list *)malloc(sizeof(t_list));
	if (!new_elem)
		return (NULL);
	new_elem->fd = fd;
	new_elem->buff = (char*)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!new_elem->buff)
	{
		free(new_elem);
		return (NULL);
	}
	new_elem->char_c = 0;
	new_elem->next = NULL;
	return (new_elem);
}

t_list		*thread_cycle(t_list **head, int fd)
{
	t_list				*current;

	if (!*head)
	{
		*head = ft_lstnew(fd);
		return (!head ? NULL : *head);
	}
	current = *head;
	while (current)
	{
		if (current->fd == fd)
			break ;
		if (!current->next)
		{
			current->next = ft_lstnew(fd);
			if (!current->next)
				return (NULL);
			current = current->next;
			break ;
		}
		current = current->next;
	}
	return (current);
}

int			ft_read(int fd, t_list *current, char **temp)
{
	int					read_ret;
	size_t				i;

	if (current->char_c == 0)
	{
		read_ret = read(fd, current->buff, BUFFER_SIZE);
		if (read_ret == EOF_ || read_ret == ERROR)
			return (read_ret);
		current->buff[read_ret] = '\n';
		current->char_c = read_ret;
	}
	i = ft_strlen(current->buff);
	*temp = copy_buff(*temp, current->buff, i);
	if (!*temp)
		return (ERROR);
	if (i < current->char_c)
	{
		current->char_c = current->char_c - i - 1;
		ft_memcpy(current->buff, current->buff + (i + 1), current->char_c + 1);
		return (LINE_READ);
	}
	else
		current->char_c = 0;
	return (LOOP);
}

int			get_next_line(int fd, char **line)
{
	static		t_list	*head;
	t_list				*current;
	t_ret_val			ret_val;
	char				*temp;

	ret_val = LOOP;
	temp = NULL;
	current = thread_cycle(&head, fd);
	if (!current)
		return (ERROR);
	while (ret_val == LOOP)
		ret_val = ft_read(fd, current, &temp);
	if (ret_val == EOF_ || ret_val == LINE_READ)
	{
		*line = copy_buff(temp, "", 0);
		if (ret_val == EOF_)
			free_buff(&head, fd);
		if (!*line)
			return (ERROR);
	}
	if (ret_val == ERROR)
		free_buff(&head, fd);
	return (ret_val);
}
