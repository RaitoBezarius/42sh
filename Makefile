##
## Makefile for mysh in /home/bebe-b_h/rendu/minishell1
## 
## Made by Hendy-Wilson BEBE-BELL
## Login   <bebe-b_h@epitech.net>
## 
## Started on  Tue Apr 14 04:32:39 2015 Hendy-Wilson BEBE-BELL
## Last update Wed Jun 03 14:10:02 2015 BEBE-BELL Hendy-Wilson
##

NAME	=	42sh

CC	=	gcc
RM	=	rm -f

SRCS	=	src/test.c				\
		src/utils/linked_list.c			\
		src/utils/line_to_wordtab.c \
		src/utils/wordtab_to_str.c \
		src/utils/strcut.c			\
		src/alias/alias.c						\
		src/alias/alias_utils.c			\
		src/env/env_utils.c			\
		src/env/env.c				\
		src/execution/execute_ast.c		\
		src/execution/child.c			\
		src/parsing/parse_passes.c		\
		src/parsing/state.c			\
		src/parsing/ast.c			\
		src/parsing/parse.c \
		src/parsing/error.c \
		src/parsing/redirection_matchers.c \
		src/parsing/matchers/pipe_redirection.c \
		src/parsing/matchers/simple_redirection.c \
		src/parsing/matchers/execution_chains.c \
		src/parsing/matchers/execution_parallel.c \
		src/parsing/token_matchers.c \
		src/parsing/command_matcher.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS	+=	-Wall -Wextra -pedantic
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
