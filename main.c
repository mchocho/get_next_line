/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchocho <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 13:18:37 by mchocho           #+#    #+#             */
/*   Updated: 2019/08/19 15:04:55 by mchocho          ###   ########.fr       */
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

	if (argc != 2)
		return (1);

	fd = open(argv[1], O_RDONLY);
	i = 0;
	ft_putstr("Reading from source \"");
	ft_putstr(argv[1]);
	ft_putstr("\":\n");
	/*if (*/get_next_line(fd, arr);/* > 0)*/
	/*{
		ft_putstr(*arr);
		ft_putchar('\n');
		free(arr);
		i++;
	} else {
		ft_putstr("Failed to read from descriptor!");
		ft_putstr(argv[1]);
		ft_putchar('\n');
	}*/
	//ft_putnbr(i);
	close(fd);
	return (0);
}
