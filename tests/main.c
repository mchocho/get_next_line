#include <fcntl.h>
#include "../includes/get_next_line.h"

int main(int argc, char **argv)
{
	ft_putstr("Testing get_next_line.c\n");

	int fd;
	int result;
	char *arr;
	arr = NULL;

	//ft_putstr("Buff size: ");
	//ft_putnbr(BUFF_SIZE);
	//ft_putstr("\n-------------------\n");
	//ft_putstr("Max Size: ");
	//ft_putnbr(MAX_SIZE);
	//ft_putstr("\n--------------------\n");

	if (argc != 2)
		return (0);

	fd = open(argv[1], O_RDONLY);
	while((result = get_next_line(fd, &arr)) == 1)
	{
		ft_putstr(arr);
		free(arr);
	}
	ft_putstr("\n\nGNL returned: ");
	ft_putnbr(result);
	close(fd);
	return (0);
}
