# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchocho <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/16 10:19:51 by mchocho           #+#    #+#              #
#    Updated: 2019/07/16 10:33:43 by mchocho          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=	get_next_line.a

HEADER=	get_next_line.h

FLAGS=	-Wall -Werror -Wextra -c

SRC=	get_next_line.c

OBJECT:=	get_next_line.o

$(NAME):
	$(MAKE) -C ./libft
	gcc $(FLAGS) $(SRC) $(HEADERS)
	ar rv $(NAME) $(OBJECT)
	rm -f *.gch
	
run:	
	gcc $(FLAGS) main.c $(NAME) libft/libft.a
	./a.out ./a.exe

all:	$(NAME)

clean:
	rm -f $(OBJECT) *.gch *.stackdump *.dSYM *.exe libft/*.o

fclean:	clean
	rm -f $(NAME) #libft/libft.a

re:	fclean all

norm:
	norminette $(FN)

compile:
	gcc $(FLAGS) $(FN)

exe:
	./a.out

exeW:
	./a.exe

.PHONY: re, clean, fclean, all
