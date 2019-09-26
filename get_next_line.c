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

	temp = ft_strjoin(str, buffer);
	return (temp);
}


static char		*ft_getline(char *str, char **line, int i)
{
	char *temp;
	
	if ((i = ft_strichrfromindex(str, '\n', i)) > -1)
		*line = ft_strsub(str, 0, i);
	else
		*line = ft_strdup(str);
	if (ft_strcmp(*line, str) == 0)
		str = NULL;
	else
	{
		temp = str;
		str = ft_strsub(str, i + 1, ft_strlen(str + (i + 1)));
		free(temp);
	}
	return (str);
}

int			get_next_line(const int fd, char **line)
{
	static char		*str;
	char			buffer[BUFF_SIZE + 1];
	int			result;
	int			i;

	if (fd < 0 || read(fd, buffer, 0) < 0 || BUFF_SIZE < 0)
		return (-1);
	i = 0;
	if (str == NULL)
		str = ft_strnew(0);
	while ((result = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[result] = '\0';	
		str = ft_concatbuffers(str, buffer);
		if (ft_strichrfromindex(str, '\n', (i * BUFF_SIZE)) > -1)
			break ;
		i++;
	}
	if (result < BUFF_SIZE && ft_strlen(str) == 0)
		return (0);
	str = ft_getline(str, line, i * BUFF_SIZE);
	return (1);
}
