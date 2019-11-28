/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchocho <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:58:28 by mchocho           #+#    #+#             */
/*   Updated: 2019/09/17 14:24:15 by mchocho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static void		ft_initlist(l_list **list)
{
	if (*list == NULL)
		return ;
	(*list)->current = NULL;
	(*list)->head = NULL;
	(*list)->tail = NULL;
}

static void		ft_addtail(l_list **list, char *str, size_t length)
{
	t_line *line;

	if (*list == NULL || !(line = (t_line *)malloc(sizeof(t_line))))
		return ;
	line->str = ft_strdup(str);
	line->length = length;
	line->next = NULL;
	if ((*list)->head == NULL)
		(*list)->head = line;
	else
		(*list)->tail->next = line;
	(*list)->tail = line;
}

static void		ft_cleanher(l_list **list, int all)
{
	t_line	*next;

	if (*list == NULL)
		return ;
	(*list)->current = (*list)->head;
	next = (*list)->current->next;
	ft_strcleandel(&(*list)->current->str);
	(*list)->current->length = 0;
	(*list)->current->next = NULL;
	free((*list)->current);
	(*list)->head = next;
	(*list)->current = (*list)->head;
	if (all)
	{
		(*list)->tail = NULL;
		free(*list);
		*list = NULL;
	}
}

static int		ft_concatbuffers(l_list **list, char **line, int i)
{
	char 	temp_1[MAX_SIZE];
	char	*temp_2;
	int	j;
	int	k;
	
	if (list == NULL)
		return 0;
	j = 0;
	ft_bzero(temp_1, 42);
	(*list)->current = (*list)->head;
	while ((*list)->current != NULL)
	{
		if ((*list)->current->next == NULL || (k = (ft_strichr((*list)->current->str, '\n')) ) > -1 ) {
			if (i > -1)
			{
				ft_strncat(temp_1, ((char *)(*list)->current->str), (size_t)i + 1);
				if ((size_t)i < (*list)->current->length)
				{
					temp_2 = (*list)->current->str;
					(*list)->current->str = ft_strsub(temp_2, i + 1, (*list)->current->length - i);
					free(temp_2);
					break;
				}
			}
			else
				ft_strcat(temp_1, (*list)->current->str);
			ft_cleanher(list, 1);
			break;
		} else
			ft_strcat(temp_1, (*list)->current->str);
		ft_cleanher(list, 0);
		j++;
	}
	if (temp_1[0] != '\0') {
		*line = (k > -1) ? ft_strndup(temp_1, k) : ft_strdup(temp_1);
		return (1);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	int		result;
	int		i;
	char		buffer[BUFF_SIZE + 1];
	static l_list	*temp;

	if (fd < 0 || read(fd, buffer, 0) < 0 || BUFF_SIZE < 0)
		return (-1);
	if (temp == NULL)
	{
		if (!(temp = (l_list *)malloc(sizeof(l_list))))
			return (-1);
		ft_initlist(&temp);
	}
	else
	{
		temp->current = temp->head;
		while (temp->current != NULL)
		{
			if ((i = ft_strichr(temp->current->str, '\n')) > -1)
				return ft_concatbuffers(&temp, line, i);
			temp->current = temp->current->next;
		}
	}
	while ((result = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[result] = '\0';
		ft_addtail(&temp, buffer, (size_t)result);
		if ((i = ft_strichr(buffer, '\n')) > -1)
			break;
	}
	return ft_concatbuffers(&temp, line, i);
}
