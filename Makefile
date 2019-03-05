##
## Makefile for  in /home/liege_m/rendu/PSU_2015_myftp
## 
## Made by maxime liege
## Login   <liege_m@epitech.net>
## 
## Started on  Mon May  2 17:34:14 2016 maxime liege
## Last update Sat May  7 20:53:38 2016 maxime liege
##

NAME		= 	server

SRC		= 	main.c \
			param_socket.c \
			handle_client.c \
			cmd_login.c \
			cmd_dir.c \
			cmd_pasv.c \
			cmd_port.c \
			cmd_data_transfer.c \
			data_channel.c \
			data_utils.c

OBJ		=	$(SRC:.c=.o)

CFLAGS		= 	-W -Wall -Wextra

CC		= 	gcc

RM		= 	rm -f

$(NAME): 		$(OBJ)
			$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

all: 			$(NAME)

clean:
			$(RM) $(OBJ)

fclean: 		clean
			$(RM) $(NAME)

re: 			fclean all
