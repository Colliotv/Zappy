/*
** create_socket.c for  in /home/kiril/project/PSU_2013_myirc/sources/client_dir
** 
** Made by Kiril
** Login   <kiril@epitech.net>
** 
** Started on  Sun Apr 27 17:08:43 2014 Kiril
** Last update Sun Apr 27 17:34:15 2014 Kiril
*/

#include 	"client.h"
#include  <iostream>

int		CreateSocket(t_socket *so, char *num_port)
{
//  num_port++;
  so->port = atoi(/*num_port*/"42424");
  so->pe = getprotobyname("TCP");
  so->s =  socket(AF_INET, SOCK_STREAM, so->pe->p_proto);
  if (so->s == -1)
    {
      write(2, "socket", strlen("socket"));
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}

int		ConnectToServer(t_socket *so, char *addr)
{
//  addr++;
  so->sin.sin_family = AF_INET;
  so->sin.sin_port = htons(so->port);
  so->sin.sin_addr.s_addr = inet_addr("127.0.0.1"/*addr*/);
  so->error = connect(so->s, (const struct sockaddr *)&so->sin,
		      sizeof(so->sin));
  if (so->error == -1)
  {
    std::cout << "fail connect\n";
  	return (EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}

int	my_connect(int	*cs, char *ip, char *hostname)
{
  t_socket	so;

  /*write(1, "[", 1);
  write(1, ip, strlen(ip));
  write(1, hostname, strlen(hostname));
  write(1, "]", 1);
  sleep(1);
  write(1, "-", 1);*/
  if (CreateSocket(&so, ip) == EXIT_FAILURE)
    {
      printf("{%s}\n", ERROR);
      return (EXIT_FAILURE);
    }
  else if (ConnectToServer(&so, hostname) == EXIT_FAILURE)
    {
      printf("[%s]\n", ERROR);
      return (EXIT_FAILURE);
    }
  *cs = so.s;
  write(so.s, "GRAPHIC\n", strlen("GRAPHIC\n"));
  return (EXIT_SUCCESS);
}
