/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchocho <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 13:18:37 by mchocho           #+#    #+#             */
/*   Updated: 2019/08/02 13:55:56 by mchocho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main(int argc, char **argv)
{
	ft_putstr("Testing get_next_line.c\n");

	int fd;
	int i;
	//char *line;
	char **arr = NULL;

	if (argc <= 1)
		return (1);

	fd = open(argv[1], O_RDONLY);
	i = 0;
	while (get_next_line(fd, arr) > 0)
	{
		ft_putstr(*arr);
		ft_putchar('\n');
		free(arr);
		i++;
	}
	ft_putchar(i);
	close(fd);
	return (0);
}
