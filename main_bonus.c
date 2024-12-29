#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	reader(char *file)
{
	int fd;
	int	i = 1;
	char *line;
	char *temp;
	int	has_newline = 0;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("\n\n\033[31mErreur lors de l'ouverture du fichier %s\033[0m\n\n\n", file);
		fflush(stdout);
		return (0);
	}
	printf("\033[31m╭━━━━═══╕出 ❖ Contenu %s ❖ 力╒═══━━━━╮\033[0m\n\n", file); fflush(stdout);
	while ((line = get_next_line(fd)) != NULL)
		{
			if (*line == '\0')
			{
				printf("\033[31mRetour de '\\0' non désiré à la ligne %i\033[0m\n", i); fflush(stdout);
				printf("\n\033[31m╰━━━━═══╕出 ❖ ————————");
				while(*file++)
					printf("—");
				printf(" ❖ 力╒═══━━━━╯\033[0m\n");
				printf("\nStatus : \033[31mFAILED\033[0m ❌\n\n\n");
				free(line);
				return (fd);
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
		printf("\n\033[31m╰━━━━═══╕出 ❖ ————————");
		while(*file++)
			printf("—");
		printf(" ❖ 力╒═══━━━━╯\033[0m\n");
		if (line != NULL)
			printf("\nStatus : \033[31mFAILED\033[0m ❌\n\n\n");
		else
			printf("\nStatus : \033[32mSUCCESS\033[0m ✅\n\n\n");
		free(line);
	return (fd);
}

int main(void)
{
	int fd1, fd2, fd3;

    fd1 = reader("ArcaneSynopsis.txt");
    // Réinitialisation du descripteur de fichier fd1
    lseek(fd1, 0, SEEK_SET);

	fd2 = reader("CyberpunkSynopsis.txt");
    fd1 = reader("ArcaneSynopsis.txt");
	fd3 = reader("multiple_nl.txt");

    close(fd1);
    close(fd2);
	close(fd3);

	printf("\033[32mTout s'est passé correctement :DD\033[0m");
	printf("\n\n╰━━━━═══╕出 ❖ —————————————————————————— ❖ 力╒═══━━━━╯\n\n\n");
	
    return (0);
}
