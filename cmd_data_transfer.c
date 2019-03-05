/*
** cmd_data.c for  in /home/liege_m/rendu/PSU_2015_myftp
** 
** Made by maxime liege
** Login   <liege_m@epitech.net>
** 
** Started on  Thu May  5 18:10:48 2016 maxime liege
** Last update Fri May  6 22:29:21 2016 maxime liege
*/

#include "myftp.h"

int	cmd_dele(int sock, t_login *login, char *buff)
{
  if (is_login(sock, login))
    {
      if (buff == NULL)
	{
	  write(sock, "501 Missing parameters.\r\n", 25);
	  return (1);
	}
      if (remove(buff) == -1)
	{
	  write(sock, "550 permission denied.\r\n", 24);
	  return (1);
	}
      write(sock, "250 file successfully deleted.\r\n", 32);
    }
  return (1);
}

int	cmd_retr(int sock, t_login *login, char *buff)
{
  FILE	*fp;
  
  if (is_login(sock, login))
    {
      if (login->state == NORMAL)
	{
	  write(sock, "425 Use PORT or PASV first.\r\n", 30);
          return (1);
	}
      if (buff != NULL)
	{
	  if ((fp = fopen(buff, "rb")) == NULL)
	    {
	      write(sock, "450 file not found or locked.\r\n", 31);
	      return (1);
	    }
	  do_retr_file(sock, login, fp);
	}
      else
	write(sock, "500 filename is missing.\r\n", 26);
      login->state = NORMAL;
    }
  return (1);
}

int	cmd_stor(int sock, t_login *login, char *buff)
{
  if (is_login(sock, login))
    {
      if (login->state == NORMAL)
	{
	  write(sock, "425 Use PORT or PASV first.\r\n", 30);
          return (1);
	}
      if (buff != NULL)
	do_stor_file(sock, login, buff);
      else
	write(sock, "500 filename is missing.\r\n", 26);
      login->state = NORMAL;
    }
  return (1);  
}
