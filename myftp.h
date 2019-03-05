/*
** myftp.h for  in /home/liege_m/rendu/PSU_2015_myftp
** 
** Made by maxime liege
** Login   <liege_m@epitech.net>
** 
** Started on  Mon May  2 12:28:01 2016 maxime liege
** Last update Sun May  8 23:04:19 2016 maxime liege
*/

#ifndef MYFTP_H_
# define MYFTP_H_

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <netdb.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <signal.h>

#include <time.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

# define NORMAL 0
# define PASSIV 1
# define PORT 2

typedef struct	s_login
{
  short		state;
  char		*ip_serv;
  char		*addr;
  uint16_t	port;
  char		*user;
  char		*pass;
  short		login;
  char		*p_dir;
  int		sdata;
}		t_login;

typedef struct	s_func
{
  int		(*ptr)(int sock, t_login *login, char *buff);
  char		*cmp;
}		t_func;

void	do_ls(int, t_login *, char *);
void	do_retr_file(int, t_login *, FILE *);
void	do_stor_file(int, t_login *, char *);
void    init_client(int, t_login *, struct sockaddr_in *);
void	to_lower_case(char **);
void	client_message(char *, char *);
void	param_socket(struct sockaddr_in *, int);
int	open_socket(int, int, char *);
void	reuse_socket(int);
void	handle_client(int, struct sockaddr_in *, char *);
short	loop_func(int, char *, t_login *);
int	is_login(int, t_login *);
char	*getpwd();
void	write_ip(int, t_login *, int);
int	create_data_transfer(int, int);
char	*get_ip_server(int);
void	data_channel_accept(t_login *);
char	**str_split(char *, const char);
int	connect_to_client(int, char *);
void	fill_client(struct sockaddr_in *, char *, char **);
int	check_buffer(char *);

/*
** Func COMMANDS
*/
int	cmd_user(int, t_login *login, char *buff);
int	cmd_pass(int, t_login *login, char *buff);
int	cmd_quit(int, t_login *login, char *buff);
int	cmd_noop(int, t_login *login, char *buff);
int	cmd_cwd(int, t_login *login, char *buff);
int	cmd_cdup(int, t_login *login, char *buff);
int	cmd_pwd(int, t_login *login, char *buff);
int	cmd_help(int, t_login *login, char *buff);
int	cmd_list(int, t_login *login, char *buff);
int	cmd_pasv(int, t_login *login, char *buff);
int	cmd_port(int, t_login *login, char *buff);
int	cmd_syst(int, t_login *login, char *buff);
int	cmd_type(int, t_login *login, char *buff);
int	cmd_dele(int, t_login *login, char *buff);
int	cmd_retr(int, t_login *login, char *buff);
int	cmd_stor(int, t_login *login, char *buff);

#endif /* MYFTP_H_ */
