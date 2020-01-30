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

static int		ft_readFile(l_list **list, int fd)
{
	char		buffer[BUFF_SIZE + 1];
	int		result;
	int		i;

	while ((result = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[result] = '\0';
		ft_addtail(list, buffer, (size_t)result);
		if ((i = ft_strichr(buffer, '\n')) > -1)
			break ;
	}
	return (i);
}

static char		*ft_getline(l_list **list, int *i, int *j)
{
	char    temp_1[MAX_SIZE];

	if (*list == NULL)
		return (NULL);
	ft_bzero(temp_1, 1);
	if (*i > -1)
	{
		ft_strncat(temp_1, (*list)->current->str, (size_t)*i);
		*j = (BUFF_SIZE * (*j)) + *i;
		if ((size_t)(*i) + 1 < (*list)->current->length)
		{
			ft_strsplice(list, (*i + 1));
			return (ft_strdup(temp_1));
		}
	}
	else
		ft_strcat(temp_1, (*list)->current->str);
	ft_cleanher(list, 1);
	return (ft_strdup(temp_1));
}

static int		ft_concatbuffers(l_list **list, char **str, int *i, int *j)
{
	t_line	*current;
	char 	*temp;

	current = (*list)->current;
	if (*str == NULL)
		*str = ft_strnew(0);
	if (current->next == NULL || current->str[*i] == '\n')
	{
		temp = ft_getline(list, i, j);
		ft_concatstr(str, temp);
		ft_strcleandel(&temp);
		return (1);
	}
	ft_concatstr(str, (*list)->current->str);
	ft_cleanher(list, 0);
	return (0);
}

static int		ft_scanbuffers(l_list **list, char **line, int i)
{
	char 	*str;
	int	j;
	
	if (*list == NULL)
		return 0;
	(*list)->current = (*list)->head;
	if ((*list)->current == NULL)
		return 0;
	j = 0;
	str = ft_strnew(0);
	while ((*list)->current != NULL)
	{
		if (ft_concatbuffers(list, &str, &i, &j))
			break;
		j++;
	}
	if (str[0] != '\0' || i > -1)
	{
		*line = (i > -1) ? ft_strndup(str, j) : ft_strdup(str);
		ft_strcleandel(&str);
		return (1);
	}
	ft_strcleandel(&str);
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	int		i;
	char		buffer[1];
	static l_list	*list;

	if (fd < 0 || read(fd, buffer, 0) < 0 || BUFF_SIZE <= 0)
		return (-1);
	if (list != NULL)
	{
		list->current = list->head;
		while (list->current != NULL)
		{
			if ((i = ft_strichr(list->current->str, '\n')) > -1)
				return ft_scanbuffers(&list, line, i);
			list->current = list->current->next;
		}
	} else {
		list = (l_list *)malloc(sizeof(l_list));
		ft_initlist(&list);
	}
	i = ft_readFile(&list, fd);
	return ft_scanbuffers(&list, line, i);
}
