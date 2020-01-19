/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchocho <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 14:45:55 by mchocho           #+#    #+#             */
/*   Updated: 2020/01/19 15:43:20 by mchocho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static char		*ft_getline(l_list **list, int *i, int *j)
{
	char    temp_1[MAX_SIZE];
	char	*temp_2;
	char	*str;
	size_t	length;

	if (*list == NULL)
		return (NULL);
	str = (*list)->current->str;
	length = (*list)->current->length;
	ft_bzero(temp_1, 1);
	if (*i > -1)
	{
		ft_strncat(temp_1, (*list)->current->str, (size_t)*i);
		*j = (BUFF_SIZE * (*j)) + *i;
		if ((size_t)(*i) + 1 < (*list)->current->length)
		{
			temp_2 = ft_strsub(str, (*i) + 1, length - ((*i) + 1));
			ft_strcleandel(&(*list)->current->str);
			(*list)->current->str = temp_2;
			(*list)->current->length = length - ((*i) + 1);
			return (ft_strdup(temp_1));
		}
	}
	else
			ft_strcat(temp_1, (*list)->current->str);
	ft_cleanher(list, 1);
	return (ft_strdup(temp_1));
}

static int		ft_concatbuffers(l_list **list, char **line, int i)
{
	t_line	*current;
	char	*temp;
	char 	str[MAX_SIZE];
	int		j;
	
	if (*list == NULL)
		return 0;
	(*list)->current = (*list)->head;
	if ((*list)->current == NULL)
		return 0;
	j = 0;
	ft_bzero(str, 1);
	while ((*list)->current != NULL)
	{
		current = (*list)->current;
		if (current->next == NULL || current->str[i] == '\n')
		{
			temp = ft_getline(list, &i, &j);
			ft_strcat(str, temp);
			ft_strcleandel(&temp);
			break;
		}
			else
				ft_strcat(str, (*list)->current->str);
		ft_cleanher(list, 0);
		j++;
	}
	if (str[0] != '\0' || i > -1)
	{
		*line = (i > -1) ? ft_strndup(str, j) : ft_strdup(str);
		return (1);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	int				result;
	int				i;
	char			buffer[BUFF_SIZE + 1];
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
			break ;
	}
	return ft_concatbuffers(&temp, line, i);
}
