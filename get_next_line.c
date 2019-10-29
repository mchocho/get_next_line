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

static char		*ft_getline(char buffer[], char *str, char **line)
{
	char 	temp[BUFF_SIZE + 1];
	size_t	i;
	
	ft_bzero(&temp, BUFF_SIZE + 1);
	if ((i = (size_t)ft_strchr(buffer, '\n')) == NULL)
	{
		ft_concatbuffers(str, buffer);
		*line = str;
	}
	else
	{
		ft_memcpy(temp, buffer, i - (size_t)buffer);
		ft_concatbuffers(str, temp);
		ft_strcpy(temp, &buffer[i - (size_t)buffer]);
		ft_bzero(buffer, BUFF_SIZE + 1);
		ft_strcpy(buffer, temp);
		*line = str;
	}
	return (*line);
}

size_t			ft_consolidate_buffer(char buffer[], char *str, char **line)
{
	if (buffer[0] != 0)
	{
		if (ft_strchr(buffer, '\n'))
		{
			return (1);
		}
		ft_concatbuffers(str, buffer);
		//return (0);
	}
	return (0;
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
	char		*str;
	static char	buffer[BUFF_SIZE + 1];
	int		result;
	int		i;

	if (fd < 0 || read(fd, buffer, 0) < 0 || BUFF_SIZE < 0)
		return (-1);
	i = 0;
	str = NULL;
	ft_consolidate_buffer(buffer, str, line);
	while ((result = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		if (!result && str == NULL)
			return (0);
		buffer[result] = '\0';
		if ((i = ft_strichrfromindex(buffer, '\n', BUFF_SIZE)) >= 0)
			break ;
		str = ft_concatbuffers(str, buffer);
	}
	ft_getline(buffer, str, line);
	return (1);
}
