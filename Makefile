##
## Makefile for mysh in /home/bebe-b_h/rendu/minishell1
## 
## Made by Hendy-Wilson BEBE-BELL
## Login   <bebe-b_h@epitech.net>
## 
## Started on  Tue Apr 14 04:32:39 2015 Hendy-Wilson BEBE-BELL
## Last update Fri May 22 18:56:52 2015 BEBE-BELL Hendy-Wilson
##

NAME	=	mysh

CC	=	gcc
RM	=	rm -f

SRCS	=	src/test.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS	+=	-Wall -Wextra
CFLAGS	+=	-ansi -pedantic
CFLAGS	+=	-Iinclude/
CFLAGS	+=	-g3

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
