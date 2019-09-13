#include "get_next_line.h"

int main(int argc, char **argv)
{
	ft_putstr("Testing get_next_line.c\n");

	int fd;
	//int i;
	//char *line;
	char *arr;
	arr = NULL;

	if (argc != 2)
		return (1);

	fd = open(argv[1], O_RDONLY);
	//i = 0;
	ft_putstr("Reading from source \"");
	ft_putstr(argv[1]);
	ft_putstr("\":\n");
	int result = /*if (*/get_next_line(fd, &arr);/* > 0)*/
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
	if (result == 1)
		ft_putstr("GNL found new line. EUREKA\n");
	else if (result == 0)
		ft_putstr("GNL read the file but found no new line!\n");
	else ft_putstr("GNL failed to run\n");
	ft_putstr("Contents of str array:\n");
	ft_putstr(arr);
	close(fd);
	return (0);
}
