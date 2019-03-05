/*
** main.c for  in /home/liege_m/rendu/sockets
** 
** Made by maxime liege
** Login   <liege_m@epitech.net>
** 
** Started on  Wed Apr 27 21:27:15 2016 maxime liege
** Last update Sun May  8 23:04:29 2016 maxime liege
*/

#include "myftp.h"

int			check_buffer(char *buff)
{
  char			*tmp;
  int			nb;
  int			dot;

  tmp = buff;
  nb = 0;
  dot = 0;
  while (*tmp)
    {
      if (*tmp >= 48 && *tmp <= 57)
        nb++;
      else if (*tmp == 44)
        dot++;
      tmp++;
    }
  if (nb++ <= 18 && dot == 5)
    return (1);
  return (0);
}

void		reuse_socket(int sock)
{
  int		_true;
  
  _true = 1;
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &_true,
		 sizeof(int)) < 0)
    {
      close(sock);
      printf("setsockopt failed\n");
      return;
    }
}

int		main(int ac, char **av)
{
  int		sock;

  srand(time(NULL));
  if (ac != 3)
    {
      printf("USAGE: ./myftp [port] [path].\n");
      return (-1);
    }
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      close(sock);
      printf("Create socket failed.\n");
      return (-2);
    }
  reuse_socket(sock);
  open_socket(sock, atoi(av[1]), av[2]);
  return (0);
}
