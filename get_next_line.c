/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchocho <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:58:28 by mchocho           #+#    #+#             */
/*   Updated: 2019/08/19 13:50:42 by mchocho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

static char		*ft_concatbuffers(char *str, char *buffer)
{
	char	*temp;
	size_t	length;

	length = ft_strlen(str) + ft_strlen(buffer);
	if (!(temp = ft_strnew(length)))
		return (NULL);
	temp = ft_strcat(temp, str);
	temp = ft_strcat(temp, buffer);
	free(str);
	return (temp);
}

static char		*ft_getline(char **line, char *str, int i)
{
	char	*temp;
	int		j;

	if ((j = ft_strichrfromindex(str, '\n', (i * BUFF_SIZE))) > -1)
	{
		*line = ft_strndup(str, j);
		if (ft_strcmp(*line, str) == 0)
		{
			ft_strdel(&str);
			str = NULL;
		}
		else
		{
			temp = str;
			str = ft_strsub(str, j + 1, ft_strlen(str + (j + 1)));
			ft_strdel(&temp);
			free(temp);
			return (str);
		}
	}
	return (NULL);
}

int				get_next_line(const int fd, char **line)
{
	static char		*str;
	char			buffer[BUFF_SIZE + 1];
	int				result;
	int				i;

	if (fd < 0 || read(fd, buffer, 0) < 0 || !line || BUFF_SIZE < 0)
		return (-1);
	i = 0;
	//if (str == NULL)
	//{
		if (!(str = ft_strnew(1)))
			return (-1);
	//}
	while ((result = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[result] = '\0';
		str = ft_concatbuffers(str, buffer);
		ft_putstr(buffer);
		if (ft_strichrfromindex(str, '\n', (i * BUFF_SIZE)) > -1)
			break ;
		i++;
	}
	if (ft_strichrfromindex(str, '\n', (i * BUFF_SIZE)) == -1 || ft_strlen(str) == 0)
		return (0);
	str = ft_getline(line, str, i);
	return (-1);
}
