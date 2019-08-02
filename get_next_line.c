/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchocho <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:58:28 by mchocho           #+#    #+#             */
/*   Updated: 2019/08/02 18:20:47 by mchocho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

char *ft_chrsub(char *str, char find, char sub)
{
	if (str == NULL)
		return (NULL);
	while (*str)
	{
		if (*str == find)
		{
			*str = sub;
			return (str);
		}
	}
	return (NULL);
}

static void		ft_readinput(const int fd, char **list)
{
	char	*input;
	char	*temp;
	char	buffer[BUFF_SIZE + 1];
	int		result;

	while (ft_strchr(list[fd], '\n') == NULL)
	{
		if ((result = read(fd, buffer, BUFF_SIZE)) == 0)
			break;
		buffer[result] = '\0';
		input = ft_strjoin(list[fd], buffer);
		ft_strdel(&list[fd]);
		temp = ft_strdup(input);
		ft_strdel(&input);
	}
}

/*void			ft_handleinput(const int fd, char **arr)
{
	char		*str1;
	char		*str2;

	str1 = ft_strdup(&array[fd]);
	str2 = ft_chrsub(&str1, '\n', '\0');
	ft_strdel(&array);
	array[fd] = ft_strdup(str2 + 1);
	*line = ft_strdup(&str1);
	ft_strdel(&str);
	return ;
}*/

int				get_next_line(const int fd, char **line)
{
	static char		*array[1024];
	char			buffer[BUFF_SIZE + 1];
	char			*str1;					//THROW IN FT_HANDLEINPUT()
	char			*str2;					//TRHOW IN FT_HANDLEINPUT()

	if (fd < 0 || read(fd, buffer, 0) < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (array[fd] == NULL)
		if (!(array[fd] = ft_strnew(1)))//(char)malloc(sizeof(char) * 1)))
			return (-1);
	*array[fd] = '\0';
	ft_readinput(fd, array);
	if (ft_strlen(array[fd]) != 0)
	{
		*line = ft_strdup(array[fd]);
		ft_strdel(&array[fd]);
	}
	else if (ft_strchr(array[fd], '\n') != NULL)
	{
		//THIS IS A FUNCTION - FT_HANDLEINPUT(**LINE)
		str1 = ft_strdup(array[fd]);
		str2 = ft_chrsub(str1, '\n', '\0');
		ft_strdel(array);
		array[fd] = ft_strdup(str2 + 1);
		*line = ft_strdup(str1);
		ft_strdel(&str1);
		//ft_handleinput(fd, array);
	}
	else
		return (0);
	return (1);
}
