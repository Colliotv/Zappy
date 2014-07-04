/*
** cmd.c for  in /home/kiril/project/PSU_2013_myirc/sources/client_dir
** 
** Made by Kiril
** Login   <kiril@epitech.net>
** 
** Started on  Sun Apr 27 17:10:08 2014 Kiril
** Last update Sun Apr 27 17:32:07 2014 Kiril
*/

#include "client.h"

int	parse_command(char ***a, char *buff)
{
  strtok(buff, " ");
  (*a)[0] = strtok(NULL, ":");
  (*a)[1] = strtok(NULL, "\0");
  if ((*a)[0] == NULL || (*a)[1] == NULL)
    {
      printf("%s\nUse: /server _host_[:_port_]\n", ERROR);
      return (-1);
    }
  return (0);
}

char    **MakeTabCmdValid()
{
  // char	**tab;

  // tab = malloc(sizeof(*tab) * 9);
  // if (tab == NULL)
  //   exit(EXIT_FAILURE);
  // tab[0] = "nick\0";
  // tab[1] = "list\0";
  // tab[2] = "join\0";
  // tab[3] = "part\0";
  // tab[4] = "users\0";
  // tab[5] = "msg\0";
  // tab[6] = "send_file\0";
  // tab[7] = "accept_file\0";
  // tab[8] = "server\0";
  return (NULL);
}

int     IsCmdValid(char **tab_cmd, char cmd[4096])
{
  int     i;

  i = 0;
  while (i < 9)
    {
      if (strncmp(tab_cmd[i], cmd, strlen(tab_cmd[i])) == 0)
	return (i);
      i++;
    }
  return -1;
}

char  *CutCmd(char cmd[4096], int i)
{
  // char  *new_cmd;
  // int   j;

//  new_cmd = malloc(sizeof(*new_cmd) * 258);
//  new_cmd = new (char);
  // if (new_cmd == NULL)
  // 	return NULL;
  // j = 0;
  // while (cmd[i] == ' ')
  //   i++;
  // while (cmd[i] != '\n' && cmd[i] != '/' && cmd[i] != '\0')
  // {
  //   new_cmd[j] = cmd[i];
  //   i++;
  //   j++;
  // }
  // new_cmd[j] = '\0';
//  return new_cmd;
  return NULL;
}

void	ParseCmd(char cmd[4096], char **nickname)
{
  char  **tab;
  int   i_cmd;

  tab = MakeTabCmdValid();
  if ((i_cmd = IsCmdValid(tab, &cmd[1])) != -1)
    {
      if (i_cmd == 0)
	*nickname = CutCmd(cmd, strlen(tab[i_cmd]) + 2);
    }
}
