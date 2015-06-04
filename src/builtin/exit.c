/*
** exit.c for 42sh in /home/bebe-b_h/projects/42sh/src/builtin
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Fri Jun 05 00:07:27 2015 BEBE-BELL Hendy-Wilson
** Last update Fri Jun 05 00:23:21 2015 BEBE-BELL Hendy-Wilson
*/
  
#include "parsing/ast.h"

int	builtin_exit(t_node_command *cmd)
{
  int	status_code;

  if (argv && argv[1])
    status_code = my_atoi(cmd->argv[1]);
  else
    status_code = 0;
  return (status_code);
}
