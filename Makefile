##
## Makefile for mysh in /home/bebe-b_h/rendu/minishell1
## 
## Made by Hendy-Wilson BEBE-BELL
## Login   <bebe-b_h@epitech.net>
## 
## Started on  Tue Apr 14 04:32:39 2015 Hendy-Wilson BEBE-BELL
## Last update Wed Jun 03 14:04:37 2015 BEBE-BELL Hendy-Wilson
##

NAME	=	mysh

CC	=	gcc
RM	=	rm -f

SRCS	=	src/test.c				\
		src/utils/my_wordtab.c			\
		src/utils/get_next_line.c		\
		src/utils/wordtab_to_str.c		\
		src/utils/linked_list.c			\
		src/alias/alias_utils.c			\
		src/env/env_utils.c			\
		src/env/env.c				\
		src/execution/execute_ast.c		\
		src/execution/child.c			\
		src/parsing/parse_passes.c		\
		src/parsing/state.c			\
		src/parsing/ast.c			\
		src/parsing/parse.c

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
