/*
** server.h for  in /home/kiril/project/PSU_2013_myirc/sources/server_dir
** 
** Made by Kiril
** Login   <kiril@epitech.net>
** 
** Started on  Sun Apr 27 17:30:21 2014 Kiril
** Last update Sun Apr 27 17:30:23 2014 Kiril
*/

#ifndef _SERVER_
#define _SERVER_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>

#define FD_FREE 0
#define FD_CLIENT 1
#define FD_SERVER 2
#define MAX_FD 255

typedef int(*fct)();

typedef struct s_client
{
  int id;
  char	*nickname;
  int   channel;
  struct s_client *next;
}	t_client;

typedef struct s_channel
{
  int   id;
  char  *channel;
  struct  s_channel *next;
} t_channel;

typedef struct s_struct
{
  char			fd_type[MAX_FD];
  fct			fct_read[MAX_FD];
  fct			fct_write[MAX_FD];
  struct protoent	*pe;
  struct sockaddr_in	sin;
  struct sockaddr_in	sin_client;
  fd_set		fd_read;
  socklen_t		client_len;
  int			s;
  int			port;
  int			error;
  char			*str;
  int			cs1;
  int			cs2;
  fd_set		readfs;
} t_socket;

int		PutStr(int fd, char *str);

char    **MakeTabCmdValid();

int     IsCmdValid(char **tab_cmd, char cmd[4096]);

void	Quit(int cs, char *cmd);

int		InitCommunication(t_socket *so, char *num_port);

int		PutStr(int fd, char *str);

void  my_show_list(t_client *list);

void    FunctJoin(t_client **list, t_channel **channel, char *cmd, int);

void    FunctServer(t_client **, int);

void    FunctPart(t_client **list, int fd);

void    FunctUsers(t_client **, int fd);

void    FunctMsg(t_client **, char *, int);

void    FunctList(t_channel **, t_client **, char *, int);

char  *my_strcpy(char *name);

void  my_show_list(t_client *list);

void  my_show_channel(t_channel *list);

int my_put_in_channel(t_channel **list, char *name);

void  SendMessage(t_client **, char *, int fd);

int     SearchChannel(t_client *list, int fd);

void  WriteInClient(char *cmd, int fd);

void    Nickname(t_client **list, char *cmd, int fd);

char    *GetNameList(t_client *client, int fd);

char  *CutCmd(char cmd[4096], int i);

void	ParseCmd(t_client **list, t_channel **channel, char cmd[4096], int fd);

int  client_read(t_socket **so, int fd, t_client **list, t_channel **channel);

void add_client(t_socket *e, int s);

int server_read(t_socket **so, int fd);

char  *CutCmd(char cmd[4096], int i);

#endif
