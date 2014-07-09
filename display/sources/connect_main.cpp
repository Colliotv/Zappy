/*
** main.c for  in /home/kiril/project/PSU_2013_myirc/sources/client_dir
** 
** Made by Kiril
** Login   <kiril@epitech.net>
** 
** Started on  Sun Apr 27 17:07:55 2014 Kiril
** Last update Sun Apr 27 17:13:52 2014 Kiril
*/

#include  <iostream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include  "client.h"
#include  "Game.hh"

void	isset_standard(char (*buff)[4096], int cs, int *len)
{
  char	*buffer;

  buffer = *buff;
//  std::cout << "[isset_standard]";
  *len = read(0, buffer, 4096);
  if (*len > 0)
  {
    buffer[*len] = 0;
    write(cs, buffer, strlen(buffer));
 }
 else if (*len == 0)
  close(cs);
}

void	Game::ClientRead(int cs)
{
  char		buffer[4096];
  int		len;
  fd_set	rdfs;
  timeval   tv;

  tv.tv_sec = 0;
  tv.tv_usec = 0;

  FD_ZERO(&rdfs);
  FD_SET(0, &rdfs);
  FD_SET(cs, &rdfs);
  memset(buffer, 0, 4096);
  if (select(cs + 1, &rdfs, NULL, NULL, &tv) == -1)
  {
    printf("SELECT ERROR\n");
    close(cs);
    return;
  }
  if (FD_ISSET(0, &rdfs))
    isset_standard(&buffer, cs, &len);
  if (FD_ISSET(cs, &rdfs))
   this->isset_server(cs);
 }

// int	connect_server(std::string   ip, std::string hostname)
// {
//   int		cs;
//   char		buff[4096];
//   char		**arg;
//   int		key;
//   int		len;

//   arg = new (char*);
//   key = 0;
//   len = 1;
// //  buff = strcat(ip.c_str(), hostname.c_str());
//   while (key != 1)
//     {
// //      len = read(0, buff, 4096);
//       if (len > 0)
//       {
//        if (strncmp("/server", buff, 7) == 0)
//        {
//         if (parse_command(&arg, buff) != -1)
//         {
//           printf("CONNECT\n");
//           key = my_connect(&cs, (char *)ip.c_str(), (char *)hostname.c_str());
//         }
//       }
//       else
//        printf("%s\nUse: /server _host_[:_port_]\n", ERROR);
//    }
//  }
//  return (cs);
// }