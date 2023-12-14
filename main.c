#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	//int		fd = open("test.txt", O_RDONLY);
	int 	fd = 0;
	char	*str;
	int		i = 0;

	str = get_next_line(fd);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		if (str)
			printf("%s", str);
		i++;
	}
	close(fd);
	return (0);
}


//TEST(/* 1 */ gnl(fd, "01234567890123456789012345678901234567890\n");
//	if (BUFFER_SIZE == 42) {
//		 /* 2 */ char c = 0; read(fd, &c, 1); check(c == '1'); ++iTest;
//	     /* 3 */ gnl(fd, NULL);}