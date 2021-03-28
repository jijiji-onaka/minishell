# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "includes/minishell.h"

int main()
{
	char *line;
	int ret ;

	int fd = open("next", O_RDONLY);
	while ((ret = get_next_line(fd, &line)))
	{
		printf("%d : %s\n", ret, line);
		free(line);
	}
	printf("%d : %s\n", ret, line);
	free(line);
	while ((ret = get_next_line(fd, &line)))
	{
		printf("%d : %s\n", ret, line);
		free(line);
	}
	printf("%d : %s\n", ret, "fi");
}
