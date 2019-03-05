/*
** param_socket.c for  in /home/liege_m/rendu/PSU_2015_myftp
** 
** Made by maxime liege
** Login   <liege_m@epitech.net>
** 
** Started on  Mon May  2 12:31:27 2016 maxime liege
** Last update Wed May  4 16:25:43 2016 maxime liege
*/

#include "myftp.h"

void		        client_message(char *ip, char *msg)
{
  if (strlen(msg) <= 1)
    return;
  write(1, ip, strlen(ip));
  write(1, " ", 1);
  write(1, msg, strlen(msg));
}

void			loop_client(int sock, char *path)
{
  struct sockaddr_in	a_sin;
  socklen_t		len;
  int			asock;
  pid_t			pid;

  len = sizeof(a_sin);
  while (42)
    {
      if ((asock = accept(sock, (struct sockaddr *) &a_sin, &len)) == -1)
	write(2, "Socket accept failed\n", 21);
      if ((pid = fork()) == 0)
	{
	  close(sock);
	  handle_client(asock, &a_sin, path);
   	  return;
	}
      else if (pid > 0)
	close(asock);
      else
	write(2, "Fork failed.\n", 13);
    }
  close(sock);
}

void			param_socket(struct sockaddr_in *sin, int port)
{
  sin->sin_family = AF_INET;
  sin->sin_port = htons(port);
  sin->sin_addr.s_addr = htonl(INADDR_ANY);
}

int			open_socket(int sock, int port, char *path)
{
  struct sockaddr_in	sin;

  param_socket(&sin, port);
  if ((bind(sock, (struct sockaddr *) &sin, sizeof(sin))) == -1)
    {
      close(sock);
      write(2, "Bind socket failed.\n", 20);
      exit(EXIT_FAILURE);
    }
  if ((listen(sock, 90000)) == -1)
    {
      close(sock);
      write(2, "Listen socket failed.\n", 22);
      exit(EXIT_FAILURE);
    }
  loop_client(sock, path);
  return (0);
}
