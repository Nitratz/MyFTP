/*
** cmd_login.c for  in /home/liege_m/rendu/PSU_2015_myftp
** 
** Made by maxime liege
** Login   <liege_m@epitech.net>
** 
** Started on  Mon May  2 21:19:14 2016 maxime liege
** Last update Fri May  6 23:19:33 2016 maxime liege
*/

#include "myftp.h"

int	cmd_help(int sock, t_login *login, char *buff)
{
  (void) buff;
  if (is_login(sock, login))
    {
      write(sock, "214-The following commands are recognized.\r\n", 44);
      write(sock, "CDUP CWD HELP NOOP PASS PWD QUIT USER\r\n", 39);
      write(sock, "214 Help OK.\r\n", 13);
    }
  return (1);
}

void	to_lower_case(char **str)
{
  int	i;

  i = -1;
  while ((*str)[++i])
    (*str)[i] = tolower((*str)[i]);
}

int	cmd_user(int sock, t_login *login, char *buff)
{
  if (login->login == 42)
    write(sock, "530 Can't change from guest user.\r\n", 35);
  else
    {
      if (buff == NULL)
	{
	  write(sock, "530 Permission denied.\r\n", 24);
	  return (1);
	}
      to_lower_case(&buff);
      login->user = strdup(buff);
      login->login = 2;
      write(sock, "331 Please specify the password.\r\n", 34);
    }
  return (1);
}

int	cmd_pass(int sock, t_login *login, char *buff)
{
  if (login->login == 42)
    {
      write(sock, "230 Already logged in.\r\n", 24);
      return (1);
    }
  if (login->login == 2)
    {
      if (buff == NULL || strcmp(buff, ""))
	{
	  write(sock, "530 Login incorrect.\r\n", 22);
	  return (1);
	}
      if (!strcmp(login->user, "anonymous"))
	{
	  client_message(login->addr, " is known as Anonymous.\n");
	  write(sock, "230 Login successful.\r\n", 23);
	  login->login = 42;
	  login->pass = strdup("");
	}
      else
	write(sock, "530 Login incorrect.\r\n", 22);
    }
  else
    write(sock, "332 Login with USER first\r\n", 27);
  return (1);
}

int	cmd_syst(int sock, t_login *login, char *buff)
{
  (void) sock;
  (void) login;
  (void) buff;
  if (is_login(sock, login))
    write(sock, "215 UNIX type: L8\r\n", 19);
  return (1);
}
