#include <fcntl.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	ft_putstr("Testing get_next_line.c\n");

	int fd;
	int result;
	char *arr;
	arr = NULL;

	if (argc != 2)
		return (0);

	fd = open(argv[1], O_RDONLY);
	while((result = get_next_line(fd, &arr)) == 1)
	{
		ft_putstr("GNL returned: ");
		ft_putnbr(result);
		ft_putstr("\n");
		ft_putendl(arr);
	}
	ft_putstr("\nGNL returned: ");
	ft_putnbr(result);
	close(fd);
	return (0);
}
