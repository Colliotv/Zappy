/*
** client.h for  in /home/kiril/project/PSU_2013_myirc/headers
** 
** Made by Kiril
** Login   <kiril@epitech.net>
** 
** Started on  Sun Apr 27 17:30:41 2014 Kiril
** Last update Sun Apr 27 17:31:16 2014 Kiril
*/

#ifndef _CLIENT_
#define _CLIENT_

#include	<unistd.h>
#include	<string.h>
#include	<stdlib.h>
#include 	<stdio.h>
#include 	<sys/socket.h>
#include 	<netinet/in.h>
#include	<arpa/inet.h>
#include	<netdb.h>
#include    <iostream>

#define ERROR "Error: cannot connect to the server"

typedef struct s_struct
{
  struct protoent		*pe;
  struct sockaddr_in	sin;
  struct sockaddr_in	sin_client;
  int					client_len;
  int					s;
  int					port;
  int					error;
  char				*str;
} t_socket;

/*		init_communication.c	*/
int		InitCommunication(t_socket *so, char *num_port);

/*		get_file_client.c		*/
void	GetFileClient(int cs, char *cmd);

/*		create_socket.c		*/
int		CreateSocket(t_socket *so, char *num_port);
int		ConnectToServer(t_socket *so, char *addr);
int		PutStr(int fd, char *str);
int	parse_command(char ***a, char *buff);
void	ParseCmd(char cmd[4096], char **nickname);
int	my_connect(int	*cs, char *, char *);

int		ConnectClientGraToServer(std::string   port);

#endif
