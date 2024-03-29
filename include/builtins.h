/*
** builtins.h for 42sh in /home/bebe-b_h/rendu/42sh/include
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Sun May 24 20:52:52 2015 BEBE-BELL Hendy-Wilson
** Last update Sun May 24 20:54:50 2015 BEBE-BELL Hendy-Wilson
*/

#ifndef BUILTINS_H_
# define BUILTINS_H_

#include "parsing/ast.h"

typedef int	(*t_builtin_ptr)(t_node_command	*);

typedef struct	s_builtin
{
  char		*name;
  t_builtin_ptr	func;
}		t_builtin;

extern t_builtin	g_builtins[];

t_builtin_ptr	get_builtin(char	*name);

#endif /* !BUILTINS_H_ */
