/*
** main.c for  in /home/kiril/project/PSU_2013_myirc/sources/client_dir
** 
** Made by Kiril
** Login   <kiril@epitech.net>
** 
** Started on  Sun Apr 27 17:07:55 2014 Kiril
** Last update Sun Apr 27 17:13:52 2014 Kiril
*/

#include 	"client.h"
#include  <iostream>

void	isset_server(int *len, int cs, char (*buff)[4096])
{
  char	*buffer;

  buffer = *buff;
  *len = read(cs, buffer, 4096);
  if (*len > 0)
    {
      buffer[*len] = 0;
      write(1, buffer, strlen(buffer));
    }
}

void	isset_standard(char **nickname, char (*buff)[4096], int cs, int *len)
{
  char	*buffer;

  buffer = *buff;
  if (*nickname == NULL)
    std::cout << "TOTO~>\n";
//    PutStr(1, "ANONYMOUS~>");
  else
    {
      write(1, *nickname, strlen(*nickname));
//      PutStr(1, "~>");
      std::cout << "TOTO~>\n";
    }
  *len = read(0, buffer, 4096);
  if (*len > 0)
    {
      buffer[*len] = 0;
      if (strncmp(buffer, "/", 1) == 0)
	{
	  ParseCmd(buffer, nickname);
	}
      write(cs, buffer, strlen(buffer));
    }
  else if (*len == 0)
    close(cs);
}

void	ClientRead(int cs)
{
  char		buffer[4096];
  int		len;
  fd_set	rdfs;
  char		*nickname;

  nickname = NULL;
  while (42)
    {
      FD_ZERO(&rdfs);
      FD_SET(0, &rdfs);
      FD_SET(cs, &rdfs);
      memset(buffer, 0, 4096);
      if (select(cs + 1, &rdfs, NULL, NULL, NULL) == -1)
      {
       printf("SELECT ERROR\n");
       close(cs);
       return;
     }
     if (FD_ISSET(0, &rdfs))
       isset_standard(&nickname, &buffer, cs, &len);
     if (FD_ISSET(cs, &rdfs))
       isset_server(&len, cs, &buffer);
   }
 }

int	connect_server()
{
  int		cs;
  char		buff[4096];
  char		**arg;
  int		key;
  int		len;

//  if ((arg = malloc(sizeof(*arg) * 2)) == NULL)
//    exit(EXIT_FAILURE);
  std::cout << "connect_server\n";
  arg = new (char*);
  key = 0;
  while (key != 1)
    {
//      PutStr(1, "ANONYMOUS~>");
      std::cout << "boucle\n";
      len = read(0, buff, 4096);
      if (len > 0)
      {
       if (strncmp("/server", buff, 7) == 0)
       {
        if (parse_command(&arg, buff) != -1)
        {
          printf("CONNECT\n");
          key = my_connect(&cs, arg);
        }
      }
      else
       printf("%s\nUse: /server _host_[:_port_]\n", ERROR);
   }
 }
 return (cs);
}

int   ConnectClientGraToServer(std::string   port)
{
  int	cs;

  std::cout << port << "\n";
  std::cout << "avant\n";
  cs = connect_server();
  std::cout << "apres\n";
  if (cs != EXIT_FAILURE)
    ClientRead(cs);
  return (EXIT_SUCCESS);
}
