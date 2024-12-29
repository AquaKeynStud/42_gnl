#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd;
	int	i = 1;
	char *line;
	char *temp;
	char *file = "multiple_nl.txt";
	int	has_newline = 0;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("\n\n\033[31mErreur lors de l'ouverture du fichier %s\033[0m\n\n\n", file);
		fflush(stdout);
		return (1);
	}
	printf("\033[31m╭━━━━═══╕出 ❖ Contenu %s ❖ 力╒═══━━━━╮\033[0m\n\n", file); fflush(stdout);
	while ((line = get_next_line(fd)) != NULL)
		{
			if (*line == '\0')
			{
				printf("\033[31mRetour de '\\0' non désiré à la ligne %i\033[0m\n", i); fflush(stdout);
				free(line);
				return (0);
			}
			else
				printf("\033[34m%i	|\033[0m  %s", i, line);
			temp = line;
			while (*(temp + 1))
				temp++;
			if (*temp == '\n')
				has_newline = 1;
			else
				has_newline = 0;
			free(line);
			i++;
		}
		line = get_next_line(fd);
		if (line == NULL && has_newline)
			printf("\033[34m%i	|\033[35m  NULL\033[0m\n", i);
		else if (line == NULL && !has_newline)
			printf("\n\033[34m%i	|\033[35m  NULL\033[0m\n", i);
		printf("\033[32mTout s'est passé correctement :DD\033[0m");
		printf("\n\n\033[31m╰━━━━═══╕出 ❖ ————————");
		while(*file++)
			printf("—");
		printf(" ❖ 力╒═══━━━━╯\033[0m\n\n\n");
		free(line);
	close(fd);
	return (0);
}
