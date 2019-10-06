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

#include "get_next_line.h"
#include "libft/libft.h"

static int	ft_checkline(char **line, char **array)
{
	char	*temp;
	char	*str;
	int	i;

	str = *array;
	if ((i = ft_strichr(str, '\n')) == -1)
		return (0);
	temp = &str[i];
	*temp = '\0';
	*line = ft_strdup(*array);
	*array = ft_strdup(temp + 1);
	return (1);
}

static int	ft_getline(char **line, char **array, int fd)
{
	char	buffer[BUFF_SIZE + 1];
	char	*temp;
	int	result;

	while ((result = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[result] = '\0';
		if (*array)
		{
			temp = *array;
			*array = ft_strjoin(temp, buffer);
			ft_strdel(&temp);
		}
		else
			*array = ft_strdup(buffer);
		if (ft_checkline(line, array))
			break;
	}
	return (result > 0);
}

int			get_next_line(const int fd, char **line)
{
	static char		*array[FD_COUNT];
	int			result;
	char			buffer[1];

	if (fd < 0 || read(fd, buffer, 0) < 0 || BUFF_SIZE < 0)
		return (-1);
	if (array[fd] && ft_checkline(line, &array[fd]))
		return (1);
	result = ft_getline(line, &array[fd], fd);
	if (result != 0 || !array[fd] || *(array[fd]) == '\0')
	{
		if (!result && *line)
			*line = NULL;
		return (result);
	}
	*line = array[fd];
	array[fd] = NULL;
	return (1);
}
