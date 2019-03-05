/*
** cmd_port.c for  in /home/liege_m/rendu/PSU_2015_myftp
** 
** Made by maxime liege
** Login   <liege_m@epitech.net>
** 
** Started on  Sat May  7 20:42:06 2016 maxime liege
** Last update Sat May  7 22:24:42 2016 maxime liege
*/

#include "myftp.h"

int		cmd_port(int sock, t_login *login, char *buff)
{
  if (is_login(sock, login))
    {
      if (check_buffer(buff))
	{
	  if ((login->sdata = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	    {
	      write(sock, "530 Failed to create Port Mode.\r\n", 33);
	      return (1);
	    }
	  if (connect_to_client(login->sdata, buff) == -1)
	    {
	      write(sock, "530 Failed to create Port Mode.\r\n", 33);
	      close(login->sdata);
	    }
	  else
	    write(sock, "200 PORT successfully connected.\r\n", 34);
	}
      else
	write(sock, "500 Command PORT wrong arguments.\r\n", 35);
    }
  return (1);
}

void			fill_client(struct sockaddr_in *sin, char *addr,
				    char **port)
{
  struct hostent	*client;
  in_addr_t		ip;

  ip = inet_addr(addr);
  client = gethostbyaddr((char *) &ip, sizeof(ip), AF_INET);
  if (client == NULL)
    return;
  sin->sin_addr = *(struct in_addr *) client->h_addr;
  sin->sin_port = htons(atoi(port[4]) * 256 + atoi(port[5]) );
  sin->sin_family = AF_INET;
}



int			connect_to_client(int sock, char *buff)
{
  char			**ip;
  char			*buffer;
  struct sockaddr_in	sin;

  ip = NULL;
  buffer = NULL;
  ip = str_split(buff, ',');
  buffer = malloc(sizeof(char) * (strlen(ip[0]) + strlen(ip[1])
				  + strlen(ip[2]) + strlen(ip[3])) + 3);
  if (buffer == NULL)
    return (-1);
  sprintf(buffer, "%s.%s.%s.%s", ip[0], ip[1], ip[2], ip[3]);
  fill_client(&sin, buffer, ip);
  free(buffer);
  if (connect(sock, (struct sockaddr *) &sin, sizeof(struct sockaddr)) == -1)
      return (-1);
  return (0);
}
