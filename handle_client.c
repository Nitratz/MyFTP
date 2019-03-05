/*
** handle_client.c for  in /home/liege_m/rendu/PSU_2015_myftp
** 
** Made by maxime liege
** Login   <liege_m@epitech.net>
** 
** Started on  Mon May  2 13:08:03 2016 maxime liege
** Last update Sat May 14 15:51:33 2016 maxime liege
*/

#include "myftp.h"

t_func	cmd_tab[] =
  {
    {&cmd_user, "user"},
    {&cmd_pass, "pass"},
    {&cmd_cwd, "cwd"},
    {&cmd_cdup, "cdup"},
    {&cmd_syst, "syst"},
    {&cmd_quit, "quit"},
    {&cmd_pwd, "pwd"},
    {&cmd_pasv, "pasv"},
    {&cmd_port, "port"},
    {&cmd_quit, "quit"},
    {&cmd_list, "list"},
    {&cmd_type, "type"},
    {&cmd_dele, "dele"},
    {&cmd_retr, "retr"},
    {&cmd_stor, "stor"},
    {&cmd_help, "help"},
    {&cmd_noop, "noop"},
    {NULL, "0"}
  };

int	is_login(int sock, t_login *login)
{
  if (login->login != 42)
    {
      write(sock, "530 Please login with USER and PASS.\r\n", 38);
      return (0);
    }
  return (1);
}

int	cmd_noop(int sock, t_login *login, char *buff)
{
  (void) buff;
  if (is_login(sock, login))
    write(sock, "200 NOOP ok.\r\n", 15);
  return (1);
}

int	cmd_quit(int sock, t_login *login, char *buff)
{
  (void) buff;
  write(sock, "221 Goodbye.\r\n", 15);
  client_message(login->addr, " has disconnected from the server.\r\n");
  login->login = 0;
  if (login->user != NULL)
    free(login->user);
  if (login->pass != NULL)
    free(login->pass);
  free(login->p_dir);
  free(login->ip_serv);
  return (0);
}

void		handle_client(int sock, struct sockaddr_in *a_sin,
			      char *dir)
{
  char		buff[4096];
  t_login	login;

  init_client(sock, &login, a_sin);
  if (!access(dir, F_OK))
    {
      chdir(dir);
      login.p_dir = getpwd();
    }
  write(sock, "220 (lFTPx 1.0.0)\r\n", 19);
  client_message(login.addr, " is connected to the server.\n");
  while (login.login)
    {
      bzero(buff, 4096);
      if (read(sock, buff, 4096) == 0)
	cmd_quit(sock, &login, buff);
      client_message(login.addr, buff);
      strtok(buff, "\r");
      loop_func(sock, buff, &login);
    }
  close(sock);
}

short		loop_func(int sock, char *buff, t_login *login)
{
  int		i;
  short		ret;
  char		*tmp;

  i = 0;
  ret = 1;
  tmp = NULL;
  if (strlen(buff) == 1)
    return (1);
  strtok(buff, "\n");
  if (strchr(buff, 32))
    {
      tmp = strndup(strchr(buff, 32) + 1, strlen(strchr(buff, 32) + 1));
      strtok(buff, " ");
    }
  to_lower_case(&buff);
  while (strcmp(buff, cmd_tab[i].cmp) && strcmp(cmd_tab[i].cmp, "0"))
    i++;
  if (strcmp(cmd_tab[i].cmp, "0") && (!strcmp(buff, cmd_tab[i].cmp)))
    cmd_tab[i].ptr(sock, login, tmp);
  else
    write(sock, "500 Unknown command.\r\n", 22);
  free(tmp);
  return (ret);
}

