/*
** exec_functions.c for 42sh in /home/bebe-b_h/projects/42sh/src/execution
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Fri Jun 05 07:58:00 2015 BEBE-BELL Hendy-Wilson
** Last update Fri Jun 05 08:02:55 2015 BEBE-BELL Hendy-Wilson
*/

#include "execution/exec_functions.h"

#include <unistd.h>

/*
** TODO: search_in_path(node->argv[0]) 
** TODO: Check if argv is correctly passed and as for envp do it yourself.
*/
int	standard_execute(t_node_command *node)
{
  return (execve(node->argv[0], node->argv, NULL));
}

/*
** TODO: Search alias and replace it by its correspondance.
** When it is done, check if it is a builtin, if it is, dispatch the call to the builtin.
** If not, call standard_execute with the node modified.
*/
int	execute_alias(t_node_command *node)
{
  return (0);
}
