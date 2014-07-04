/*
** tools.c for  in /home/kiril/project/PSU_2013_myirc/sources/client_dir
** 
** Made by Kiril
** Login   <kiril@epitech.net>
** 
** Started on  Sun Apr 27 17:10:34 2014 Kiril
** Last update Sun Apr 27 17:10:35 2014 Kiril
*/

#include	"client.h"

int		PutStr(int fd, char *str)
{
	int		i;

	i = 0;
	if (str == NULL)
		return EXIT_FAILURE;
	while (str[i] != 0)
	{
		write(fd, &str[i], 1);
		i++;
	}
	if (fd == 1)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}
