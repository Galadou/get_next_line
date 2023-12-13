#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd = open("test.txt", O_RDONLY);
	char	*str;
	int		i = 0;

	while (i < 6)
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
		i++;
	}
	close(fd);
	return (0);
}
