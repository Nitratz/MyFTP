/*
** cmd_dir.c for  in /home/liege_m/rendu/PSU_2015_myftp
** 
** Made by maxime liege
** Login   <liege_m@epitech.net>
** 
** Started on  Mon May  2 22:45:18 2016 maxime liege
** Last update Sat May 14 19:57:04 2016 maxime liege
*/

#include "myftp.h"

int	cmd_list(int sock, t_login *login, char *buff)
{
  (void) buff;
  if (is_login(sock, login))
    {
      if (login->state == NORMAL)
	{
	  write(sock, "425 Use PORT or PASV first.\r\n", 30);
	  return (1);
	}
      do_ls(sock, login, buff);
      if (close(login->sdata) == -1)
	printf("Data socket close failed\n");
      login->state = NORMAL;
    }
  return (1);
}

int	cmd_cwd(int sock, t_login *login, char *buff)
{
  char	*pwd;

  if (is_login(sock, login))
    {
      if (buff != NULL)
	{
	  pwd = getpwd();
	  if (!strcmp(login->p_dir, pwd) && !strcmp(buff, ".."))
	    {
	      write(sock, "250 Directory successfully changed.\r\n", 37);
	      free(pwd);
	    }
	  else if (!access(buff, F_OK))
	    {
	      chdir(buff);
	      write(sock, "250 Directory successfully changed.\r\n", 37);
	    }
	  else
	    write(sock, "550 Failed to change directory.\r\n", 33);
	}
      else
	write(sock, "550 Failed to change directory.\r\n", 33);
    }
  return (1);
}

int	cmd_cdup(int sock, t_login *login, char *buff)
{
  char	*pwd;
 
  (void) buff;
  if (is_login(sock, login))
    {
      pwd = getpwd();
      if (!strcmp(login->p_dir, pwd))
	{
	  write(sock, "200 Directory successfully changed.\r\n", 37);
	  free(pwd);
	}
      else if (!access(login->p_dir, F_OK))
	{
	  chdir("..");
	  write(sock, "200 Directory successfully changed.\r\n", 37);
	}
      else
	write(sock, "550 Failed to change directory.\r\n", 33);
    }
  return (-1);
}

int	cmd_pwd(int sock, t_login *login, char *buff)
{
  char	*pwd;

  (void) buff;
  pwd = getpwd();
  if (is_login(sock, login))
    {
      write(sock, "257 \"", 5);
      write(sock, pwd, strlen(pwd));
      write(sock, "\"\r\n", 3);
    }
  free(pwd);
  return (1);
}

char	*getpwd()
{
  char	*dir;

  if ((dir = malloc(sizeof(char) * 1024)) == NULL)
    {
      write(2, "Malloc failed.\n", 15);
      exit(EXIT_FAILURE);
    }
  getcwd(dir, 1024);
  dir[strlen(dir) + 1] = '\0';
  return (dir);
}
