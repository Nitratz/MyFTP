/*
** cmd_transfer.c for  in /home/liege_m/rendu/PSU_2015_myftp
** 
** Made by maxime liege
** Login   <liege_m@epitech.net>
** 
** Started on  Tue May  3 20:21:24 2016 maxime liege
** Last update Sun May  8 23:11:40 2016 maxime liege
*/

#include "myftp.h"

int			cmd_pasv(int sock, t_login *login, char *buff)
{
  int			sdata;
  int			port;

  (void) buff;
  if (is_login(sock, login))
    {
      port = rand() % 535 + 65000;
      if ((sdata = create_data_transfer(sock, port)) == -1)
	{
	  write(sock, "530 Failed to create Passive Mode.\r\n", 38);
	  return (1);
	}
      login->sdata = sdata;
      write_ip(sock, login, port);
      login->state = PASSIV;
      close(sdata);
    }
  return (1);
}

int			create_data_transfer(int sock, int port)
{
  int			sdata;
  struct sockaddr_in	sin;
  int			errno;

  (void) sock;
  if ((sdata = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      printf("Create socket failed.\n");
      return (-1);
    }
  reuse_socket(sdata);
  param_socket(&sin, port);
  if ((errno = bind(sdata, (struct sockaddr *) &sin, sizeof(sin))) == -1)
    {
      close(sdata);
      write(2, "Bind data socket failed.\n", 25);
      return (-1);
    }
  if ((listen(sdata, 10)) == -1)
    {
      close(sdata);
      write(2, "Listen socket failed.\n", 22);
      return (-1);
    }
  return (sdata);
}

char			**split_loop(char *str, int count, char *delim)
{
  char			*token;
  size_t		idx;
  char			**result;
  char			*tmp;

  tmp = strdup(str);
  result = NULL;
  result = malloc(sizeof(char *) * count);
  if (result)
    {
      token = strtok(tmp, delim);
      idx = 0;
      while (token)
        {
	  *(result + idx++) = strdup(token);
	  token = strtok(0, delim);
        }
      *(result + idx) = 0;
    }
  free(tmp);
  return (result);
}

char**		str_split(char* a_str, const char a_delim)
{
  int		count;
  char*		tmp;
  char*		last_comma;
  char		delim[2];

  last_comma = NULL;
  count = 0;
  tmp = a_str;
  delim[0] = a_delim;
  delim[1] = 0;
  while (*tmp)
    {
      if (a_delim == *tmp)
        {
	  count++;
	  last_comma = tmp;
        }
      tmp++;
    }
  count += last_comma < (a_str + strlen(a_str) - 1);
  count++;
  return (split_loop(a_str, count, delim));
}

void			write_ip(int sock, t_login *login, int port)
{
  char			**ip;
  int			port_1;
  int			port_2;
  int			i;

  i = -1;
  port_1 = port / 256;
  port_2 = port - (port_1 * 256);
  ip = str_split(login->ip_serv, '.');
  printf("Passive mode on : %s.%s.%s.%s:%d\n", 
	 ip[0], ip[1], ip[2], ip[3], port);
  dprintf(sock, "227 Entering Passive Mode (%s,%s,%s,%s,%d,%d).\r\n",
  	  ip[0], ip[1], ip[2], ip[3], port_1, port_2);
  while (++i < 4)
    free(ip[i]);
  free(ip);
  data_channel_accept(login);
}
