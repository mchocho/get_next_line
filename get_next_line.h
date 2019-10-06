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

#include "libft/libft.h"
#define BUFF_SIZE 255
#define FD_COUNT 1024 + 1

int	get_next_line(const int fd, char **line);

#endif
