/*
** utils.c for  in /home/liege_m/rendu/PSU_2015_myftp
** 
** Made by maxime liege
** Login   <liege_m@epitech.net>
** 
** Started on  Thu May  5 01:10:52 2016 maxime liege
** Last update Fri May  6 23:57:04 2016 maxime liege
*/

#include "myftp.h"

void	do_ls(int sock, t_login *login, char *buff)
{
  int	fd;

  write(sock, "150 opening data connection.\r\n", 30);
  fd = dup(1);
  dup2(login->sdata, 1);
  if (buff == NULL)
    system("ls -la");
  else
    {
      if (!access(buff, F_OK))
	system(strcat("ls -la ", buff));
      else
        system("ls -la");
    }
  dup2(fd, 1);
  write(sock, "226 closing data connection.\r\n", 30);
}

void		do_stor_file(int sock, t_login *login, char *buff)
{
  FILE		*fp;
  int		buffer[2];

  write(sock, "150 opening data connection.\r\n", 30);
  if ((fp = fopen(buff, "wb")) == NULL)
    {
      write(sock, "450 file cannot be created.\r\n", 31);
      return;
    }
  while (read(login->sdata, (char *) &buffer, sizeof(buffer)))
    write(fileno(fp), (char *) &buffer, sizeof(buffer));
  fclose(fp);
  write(sock, "226 closing data connection.\r\n", 30);
  close(login->sdata);
}

void		do_retr_file(int sock, t_login *login, FILE *fp)
{
  char		*file;
  int		len;
  int		i;

  i = 0;
  file = NULL;
  write(sock, "150 opening data connection.\r\n", 30);
  fseek(fp, 0L, SEEK_END);
  len = ftell(fp);
  fseek(fp, 0L, SEEK_SET);
  if ((file = malloc(len + 1)) != NULL)
    {
      fread(file, len, 1, fp);
      while (i < len)
	i += write(login->sdata, file + i, len);
      free(file);
      write(sock, "226 closing data connection.\r\n", 30);
    }
  else
    write(sock, "426 Connexion closed, malloc failed.\r\n", 30);
  fclose(fp);
  close(login->sdata);
}

void	init_client(int sock, t_login *login, struct sockaddr_in *a_sin)
{
  login->user = NULL;
  login->pass = NULL;
  login->state = NORMAL;
  login->ip_serv = get_ip_server(sock);
  login->addr = inet_ntoa(a_sin->sin_addr);
  login->port = ntohs(a_sin->sin_port);
  login->login = 1;
}

char	*get_ip_server(int sock)
{
  struct sockaddr_in	sin;
  socklen_t		len;

  len = sizeof(sin);
  if (getsockname(sock, (struct sockaddr *) &sin, &len) == -1)
    {
      close(sock);
      write(2, "getsockname failed.\n", 20);
      exit(EXIT_FAILURE);
    }
  return (strdup(inet_ntoa(sin.sin_addr)));
}
