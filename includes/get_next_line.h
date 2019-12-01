/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchocho <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 16:57:05 by mchocho           #+#    #+#             */
/*   Updated: 2019/09/17 14:22:06 by mchocho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#define BUFF_SIZE 255
#include <fcntl.h>
#include "../libft/includes/libft.h"
#define MAX_SIZE 2147483647 / (1024 * 4)

typedef struct s_line {
	char *str;
	size_t length;
	struct s_line *next;
}	t_line;

typedef struct _linkedlist {
	struct s_line *next;
	struct s_line *head;
	struct s_line *tail;
	struct s_line *current;

}	l_list;

int	get_next_line(const int fd, char **line);

#endif
