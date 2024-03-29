##
## Makefile for mysh in /home/bebe-b_h/rendu/minishell1
## 
## Made by Hendy-Wilson BEBE-BELL
## Login   <bebe-b_h@epitech.net>
## 
## Started on  Tue Apr 14 04:32:39 2015 Hendy-Wilson BEBE-BELL
## Last update Fri Jun 05 08:34:54 2015 BEBE-BELL Hendy-Wilson
##

NAME	=	42sh

CC	=	gcc
RM	=	rm -f

SRCS	=	src/main.c					\
		src/utils/my_wordtab.c				\
		src/utils/linked_list.c				\
		src/utils/wordtab_to_str.c			\
		src/utils/get_next_line.c			\
		src/utils/strcut.c				\
		src/utils/command_type.c			\
		src/alias/alias.c				\
		src/alias/alias_utils.c				\
		src/builtin/builtin.c				\
		src/builtin/echo.c				\
		src/env/env_utils.c				\
		src/env/env.c					\
		src/execution/execute_ast.c			\
		src/execution/child.c				\
		src/execution/signal_handler.c			\
		src/execution/exec_functions.c			\
		src/path/find_exec.c				\
		src/parsing/parse_passes.c			\
		src/parsing/state.c				\
		src/parsing/ast.c				\
		src/parsing/parse.c				\
		src/parsing/parse_utils.c			\
		src/parsing/error.c				\
		src/parsing/syntax_checker.c			\
		src/parsing/redirection_matchers.c		\
		src/parsing/matchers/pipe_redirection.c		\
		src/parsing/matchers/simple_redirection.c	\
		src/parsing/matchers/execution_chains.c		\
		src/parsing/matchers/execution_parallel.c	\
		src/parsing/token_matchers.c			\
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
