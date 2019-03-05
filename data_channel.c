/*
** data_channel.c for  in /home/liege_m/rendu/PSU_2015_myftp
** 
** Made by maxime liege
** Login   <liege_m@epitech.net>
** 
** Started on  Wed May  4 21:22:54 2016 maxime liege
** Last update Fri May  6 23:16:17 2016 maxime liege
*/

#include "myftp.h"

void			data_channel_accept(t_login *login)
{
  struct sockaddr_in	a_sin;
  socklen_t		len;
  int			nsock;

  len = sizeof(a_sin);
  if ((nsock = accept(login->sdata, (struct sockaddr *) &a_sin, &len)) == -1)
    write(2, "Socket accept failed\n", 21);
  login->sdata = nsock;
}

int	cmd_type(int sock, t_login *login, char *buff)
{
  if (is_login(sock, login))
    {
      if (buff == NULL)
	{
	  write(sock, "500 Unrecognised TYPE command.\r\n", 32);
	  return (1);
	}
      to_lower_case(&buff);
      if (!strcmp(buff, "i"))
	write(sock, "200 Switching to Binary mode.\r\n", 31);
      else if (!strcmp(buff, "a"))
	write(sock, "200 Switching to ASCII mode.\r\n", 30);
      else
	write(sock, "500 Unrecognised TYPE command.\r\n", 32);
    }
  return (1);
}
