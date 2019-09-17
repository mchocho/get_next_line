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

static void		ft_cleandel(char *str)
{
	ft_strclr(str);
	ft_strdel(&str);
	return ;
}

static char		*ft_concatbuffers(char *str, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(str, buffer);
	ft_cleandel(str);
	return (temp);
}

int				get_next_line(const int fd, char **line)
{
	static char		*str;
	char			buffer[BUFF_SIZE + 1];
	int				result;
	int				i;

	if (fd < 0 || read(fd, buffer, 0) < 0 || BUFF_SIZE < 0)
		return (-1);
	i = 0;
	if (!(str = ft_strnew(1)))
		return (-1);
	while ((result = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[result] = '\0';
		str = ft_concatbuffers(str, buffer);
		if (ft_strichrfromindex(str, '\n', (i * BUFF_SIZE)) > -1)
			break ;
		i++;
	}
	if ((i = ft_strichrfromindex(str, '\n', i * BUFF_SIZE)) > -1)
		*line = ft_strsub(str, 0, i);
	else if (ft_strlen(str) > 0)
		*line = ft_strdup(str);
	ft_cleandel(str);
	return ((i == -1) ? 0 : 1);
}
